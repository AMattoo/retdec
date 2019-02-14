#ifndef RETDEC_BORLAND_AST_TYPES_H
#define RETDEC_BORLAND_AST_TYPES_H

#include <memory>
#include <string>
#include <vector>

#include "llvm/Demangle/StringView.h"
#include "llvm/Demangle/borland_ast.h"

namespace retdec {
namespace demangler {
namespace borland {

class Context;

enum class ThreeStateSignness {
	signed_char,
	unsigned_char,
	no_prefix
};

class TypeNode : public Node {
public:
	bool isVolatile() const;
	bool isConst() const;
	StringView typeName() const;

protected:
	TypeNode(const StringView &typeName, bool isVolatile, bool isConst);

	void printLeft(std::ostream &s) const override;

protected:
	StringView _typeName;
	bool _isVolatile;
	bool _isConst;
};

/**
 * @brief Node for representation of built-in types.
 */
class BuiltInTypeNode : public TypeNode
{
public:
	static std::shared_ptr<BuiltInTypeNode> create(
		Context &context,
		const StringView &typeName,
		bool isVolatile,
		bool isConst);

protected:
	BuiltInTypeNode(const StringView &typeName, bool isVolatile, bool isConst);
};

class CharTypeNode : public BuiltInTypeNode
{
public:
	static std::shared_ptr<CharTypeNode> create(
		Context &context,
		ThreeStateSignness signness,
		bool isVolatile,
		bool isConst);

	ThreeStateSignness signness();

private:
	CharTypeNode(ThreeStateSignness signness, bool isVolatile, bool isConst);

	void printLeft(std::ostream &s) const override;

private:
	ThreeStateSignness _signness;
};

class IntegralTypeNode : public BuiltInTypeNode
{
public:
	static std::shared_ptr<IntegralTypeNode> create(
		Context &context,
		const StringView &typeName,
		bool isUnsigned,
		bool isVolatile,
		bool isConst);

	bool isUnsigned();

private:
	IntegralTypeNode(const StringView &typeName, bool isUnsigned, bool isVolatile, bool isConst);

	void printLeft(std::ostream &s) const override;

private:
	bool _isUnsigned;
};

class FloatTypeNode : public BuiltInTypeNode
{
public:
	static std::shared_ptr<FloatTypeNode> create(
		Context &context,
		const StringView &typeName,
		bool isVolatile,
		bool isConst);

private:
	FloatTypeNode(const StringView &typeName, bool isVolatile, bool isConst);
};

class PointerTypeNode : public TypeNode
{
public:
	static std::shared_ptr<PointerTypeNode> create(
		Context context,
		std::shared_ptr<Node> pointee,
		bool isVolatile,
		bool isConst);

	std::shared_ptr<Node> pointee();

private:
	PointerTypeNode(std::shared_ptr<Node> pointee, bool isVolatile, bool isConst);

	void printLeft(std::ostream &s) const override;

protected:
	std::shared_ptr<Node> _pointee;
};

}    // borland
}    // demangler
}    // retdec

#endif //RETDEC_BORLAND_AST_TYPES_H
