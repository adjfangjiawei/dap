#include "node.h"

#include "src/core/utilities/file_util.h"

namespace dap::parser
{
std::string VarDecl::getName() const
{
    return name->getName();
}

const QualifiedName *VarDecl::getQualifiedName() const
{
    return name;
}

const QualifiedName *VarDecl::getType() const
{
    return type;
}

bool Node::isa(parser::NodeMetaDataType type)
{
    return metadata->getNodeType() == type;
}
} // namespace dap::parser