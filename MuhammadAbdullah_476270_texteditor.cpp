// header files
#include "texteditor.h"
#include <list>
#include <string>
#include <map>

using namespace std;

// internal structure for managing text editor data
struct TextEditorInternal
{
    list<char> text;             // list to store text characters
    list<char>::iterator cursor; // iterator representing current cursor position

    // constructor that initializes empty text and cursor at beginning
    TextEditorInternal() : text(), cursor(text.begin()) {}
};

// static global data
static map<TextEditor *, TextEditorInternal> editorRepo;

// internal helper function
TextEditorInternal &getInternal(TextEditor *editor)
{
    auto it = editorRepo.find(editor); // try to find existing internal data
    if (it == editorRepo.end())
    {
        auto &newEntry = editorRepo[editor];
        // initialize cursor to start of the text for the new editor
        newEntry.cursor = newEntry.text.begin();
        return newEntry;
    }
    return it->second; // return reference to existing internal data
}

// insert a character at the current cursor position
void TextEditor::insertChar(char c)
{
    TextEditorInternal &ed = getInternal(this); // get internal data for this editor
    ed.cursor = ed.text.insert(ed.cursor, c);   // insert char before cursor and update cursor
    ++ed.cursor;
}

// delete the character before the current cursor
void TextEditor::deleteChar()
{
    TextEditorInternal &ed = getInternal(this);

    // Remove the character before the cursor (if any)
    if (ed.cursor != ed.text.begin())
    {
        --ed.cursor;
        ed.cursor = ed.text.erase(ed.cursor); // now cursor points to the old "current" element
    }

    // Also remove the character now at the cursor (if any)
    if (ed.cursor != ed.text.end())
    {
        ed.cursor = ed.text.erase(ed.cursor);
    }
}

// move cursor one position to the left
void TextEditor::moveLeft()
{
    TextEditorInternal &ed = getInternal(this);
    if (ed.cursor != ed.text.begin())
        --ed.cursor; // move left only if not at start
}

// move cursor one position to the right
void TextEditor::moveRight()
{
    TextEditorInternal &ed = getInternal(this);
    if (ed.cursor != ed.text.end())
        ++ed.cursor; // move right only if not at end
}

// return the full text as a string, showing '|' symbol at cursor position
string TextEditor::getTextWithCursor() const
{
    TextEditorInternal &ed = getInternal(const_cast<TextEditor *>(this)); // get editable internal data
    string result;                                                        // final string to return

    // build the output string character by character
    for (auto it = ed.text.begin(); it != ed.text.end(); ++it)
    {
        if (it == ed.cursor)
            result.push_back('|');
        result.push_back(*it);
    }

    // if cursor is at the end, show '|' at the end of text
    if (ed.cursor == ed.text.end())
        result.push_back('|');

    return result;
}
