
#include "renderer.hpp"

#include "class/placeable.hpp"


namespace DF
{

Renderer Renderer::sRenderer;


void Renderer::setNode(size_t idx, osg::MatrixTransform *node)
{
    mBaseNodes[idx] = node;
}

void Renderer::remove(const size_t *ids, size_t count)
{
    while(count > 0)
        mBaseNodes.erase(ids[--count]);
}


void Renderer::markDirty(size_t idx, const Position &pos)
{
    auto iter = mBaseNodes.find(idx);
    if(iter != mBaseNodes.end())
        mDirtyNodes.push({*iter, pos});
}

void Renderer::update()
{
    while(!mDirtyNodes.empty())
    {
        const NodePosPair &nodepos = mDirtyNodes.top();

        osg::Matrix mat;
        mat.makeRotate(nodepos.mPosition.mOrientation);
        mat.postMultTranslate(nodepos.mPosition.mPoint);

        //nodepos.mNode->setDataVariance(osg::Node::DYNAMIC);
        nodepos.mNode->setMatrix(mat);

        mDirtyNodes.pop();
    }
}


} // namespace DF
