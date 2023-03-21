#ifndef NODE_HPP
#define NODE_HPP

#include <memory>

template <typename TVal, typename... TArgs>
class Node;

template <typename TVal, typename... TArgs>
using NodePtr = std::shared_ptr<Node<TVal, TArgs...>>;

template <typename T>
using TSquare = decltype(std::declval<T>() * std::declval<T>());
template <typename T1, typename T2>
using TAdd = decltype(std::declval<T1>() + std::declval<T2>());

template <typename TPtr>
using TPtrValType = typename TPtr::element_type::value_type;

template <typename TVal, typename... TPtrs>
class Node {
public:
    using value_type = TVal;

    Node(std::string func_name = "", std::string val_name = "") :
        func_name(func_name), val_name(val_name) {}

    void set_inputs(const TPtrs &... inputs) {
        this->inputs = std::make_tuple(inputs...);
    }

    void forward(void) {
        this->val = std::apply([this](const auto &... args) {
            return this->func(args->val...);
        }, this->inputs);
    }

    TVal val;

protected:
    virtual TVal func(const typename TPtrs::element_type::value_type &... args) = 0;

    std::string func_name;
    std::string val_name;
    std::tuple<TPtrs...> inputs;
};

template <typename TVal>
class Variable : public Node<TVal> {
public:
    Variable(std::string name) : Node<TVal>("", name) {}

private:
    virtual TVal func(void) {
        return this->val;
    }
};

template <typename TPtr>
class Square : public Node<TSquare<TPtrValType<TPtr>>, TPtr> {
public:
    Square() : Node<TSquare<TPtrValType<TPtr>>, TPtr>("square") {}

private:
    virtual TSquare<TPtrValType<TPtr>> func(const TPtrValType<TPtr> &arg) {
        return arg * arg;
    }
};

template <typename TPtr1, typename TPtr2>
class Add : public Node<TAdd<TPtrValType<TPtr1>, TPtrValType<TPtr2>>, TPtr1, TPtr2> {
public:
    Add() : Node<TAdd<TPtrValType<TPtr1>, TPtrValType<TPtr2>>, TPtr1, TPtr2>("add") {}

private:
    virtual TAdd<TPtrValType<TPtr1>, TPtrValType<TPtr2>> func(
        const TPtrValType<TPtr1> &arg1, const TPtrValType<TPtr2> &arg2
    ) {
        return arg1 + arg2;
    }
};

template <typename TVal>
std::shared_ptr<Variable<TVal>> variable(std::string name) {
    return std::make_shared<Variable<TVal>>(name);
}

template <typename TPtr>
std::shared_ptr<Square<TPtr>> square(const TPtr &arg) {
    auto n = std::make_shared<Square<TPtr>>();
    n->set_inputs(arg);
    return n;
}

template <typename TPtr1, typename TPtr2>
std::shared_ptr<Add<TPtr1, TPtr2>> add(const TPtr1 &arg1, const TPtr2 &arg2) {
    auto n = std::make_shared<Add<TPtr1, TPtr2>>();
    n->set_inputs(arg1, arg2);
    return n;
}

#endif
