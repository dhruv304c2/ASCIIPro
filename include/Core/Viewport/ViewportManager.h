#ifndef VIEWPORTMANAGER_H
#define VIEWPORTMANAGER_H

#include "Collection/BTree.h"
#include "Core/Viewport/Viewport.h"
#include "Core/Window.h"

using ViewportNode = BTreeNode<Viewport>;

enum class ViewportSplit{
    Horizontal,
    Vertical
};

class ViewportManager {
public:
    ViewportManager(Window* window = nullptr);
    ~ViewportManager();
    ViewportNode* split(ViewportNode* parent,ViewportSplit splitStyle, float split);
    ViewportNode* selected();
    ViewportNode* root();
    void resize();
    void select(ViewportNode* node);
    void render();
    void start();
private:
    Window* _window;
    BTree<Viewport>* _viewport_tree;
    Viewport* _root;
    ViewportNode* _selected;
};

#endif
