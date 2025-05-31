#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include <doctest/doctest.h>

#include <vector>
#include <list>
#include <string>
#include <memory>
#include <algorithm>
#include <stdexcept>

/**
 * TODO: introduce visitor interface.
 * TODO: implement character stream output using printer visitor.
 * TODO: replace operator() implementation with evaluation visitor.
 * Note:
 *  - "declare" means write a declaration only:
 *    - for function: just a signature, without body (without "{...}")
 *    - for class: just a class/struct and name, without inner details (without "{...}")
 *  - "define" means write full implementation with all details:
 *    - for function: function signature + body with "{...}"
 *    - for class: class/struct + name
 *  - "function signature" consists of:
 *    - function name,
 *    - formal parameters (at least types, names can be omitted), and
 *    - method qualifiers (const, volatile, &, &&) if the function is a member of a class.
 *    - The return value is not really part of signature.
 */


namespace calculator
{
    using state_t = std::vector<double>;

    /// Operations:
    enum class op_t { plus, minus, mul, div, assign };

    // TODO: forward-declare Visitor interface
    struct Visitor;

    /// Polymorphic interface to various terms:
    struct term_t: std::enable_shared_from_this<term_t>
    {
        // TODO: declare pure virtual "accept" method to support visitor pattern.
        virtual void accept(Visitor&) const = 0;
        // TODO: remove "virtual" part and implement it using visitor pattern down below
        double operator()(state_t&) const;

        term_t() = default;
        virtual ~term_t() noexcept = default;
        term_t(term_t&&) = delete;
        term_t& operator=(term_t&&) = delete;
    protected:
        term_t(const term_t&) = default;
        term_t& operator=(const term_t&) = default;
    };
    using term_ptr = std::shared_ptr<term_t>;
    using term_cptr = std::shared_ptr<const term_t>;

    /** Special term for a variable expression */
    class var_t final: public term_t
    {
        size_t _id; ///< index in symbol table, keeps this class super-light
        explicit var_t(size_t id): _id{id} {} ///< allow creation only in symbol table
    public:
        var_t(const var_t& other) = default; ///< enable copying of this light class
        var_t& operator=(const var_t& other) = default;
        ~var_t() noexcept override = default;
        size_t id() const { return _id; }
        // TODO: declare "accept" method override
        // TODO: move operator() code into visitor, remove operator() from here
        double operator()(state_t& s) const override { return s[_id]; }
        friend class symbol_table_t;
    };
    using var_cptr = const std::shared_ptr<const var_t>;

    class symbol_table_t
    {
        std::vector<std::string> names;
        state_t initial;
    public:
        [[nodiscard]] auto var(std::string name, double init = 0) {
            auto id = names.size();
            names.push_back(std::move(name));
            initial.push_back(init);
            return var_t{id};
        }
        [[nodiscard]] const std::string& get_name(size_t id) const { return names[id]; }
        [[nodiscard]] state_t state() const { return initial; }
    };

    class const_t final : public term_t
    {
        double _value;
    public:
        explicit const_t(double value): _value{value} {}
        double value() const { return _value; }
        // TODO: declare "accept" method override
        // TODO: move operator() code into visitor, remove operator() from here
        double operator()(state_t&) const override { return _value; }
    };

    /** Specialization for unary operations: */
    class unary_t final : public term_t
    {
        term_cptr _term;
        op_t _op;

    public:
        explicit unary_t(term_cptr term, op_t op = op_t::plus):
            _term{std::move(term)}, _op{op} {}
        const term_t& term() const { return *_term; }
        op_t op() const { return _op; }
        // TODO: declare "accept" method override
        // TODO: move operator() code into visitor, remove operator() from here
        double operator()(state_t& s) const override { return 0; }
    };

    class binary_t final : public term_t
    {
        term_cptr _t1;
        term_cptr _t2;
        op_t _op;

    public:
        binary_t(term_cptr t1, term_cptr t2, op_t op):
            _t1{std::move(t1)}, _t2{std::move(t2)}, _op{op} {}
        const term_t& term1() const { return *_t1; }
        const term_t& term2() const { return *_t2; }
        op_t op() const { return _op; }
        // TODO: declare "accept" method override
        // TODO: move operator() code into visitor, remove operator() from here
        double operator()(state_t& s) const override
        {
            return (*_t1)(s) + (*_t2)(s);
        }
    };

    class assign_t final : public term_t
    {
        var_cptr _var;
        term_cptr _term;
        op_t _op;

    public:
        assign_t(var_cptr var, term_cptr term, op_t op = op_t::assign):
            _var{std::move(var)}, _term{std::move(term)}, _op{op} {}
        const var_t& var() const { return *_var; }
        const term_t& term() const { return *_term; }
        op_t op() const { return _op; }
        // TODO: declare "accept" method override
        // TODO: move operator() code into visitor, remove operator() from here
        double operator()(state_t& s) const override { return 0;}
    };

    struct expr_t {
        term_cptr term;
        expr_t(const var_t& var): term{std::make_shared<var_t>(var)} {} // implicit for conversions
        explicit expr_t(term_cptr e): term{std::move(e)} {}
        double operator()(state_t& s) const {  return (*term)(s); }
    };

    expr_t operator+(const expr_t& e1, const expr_t& e2) {
        return expr_t{std::make_shared<binary_t>(e1.term, e2.term, op_t::plus)};
    }

    // TODO: define Visitor interface
    struct Visitor {
        virtual ~Visitor() = default;
        virtual void visit(const const_t&) = 0;
        virtual void visit(const var_t&) = 0;
        virtual void visit(const unary_t&) = 0;
        virtual void visit(const binary_t&) = 0;
        virtual void visit(const assign_t&) = 0;
    };
    // TODO: define "accept" method for const_t, var_t, unary_t, binary_t, assign_t

    // TODO: define Evaluator visitor
    // TODO: define Printer visitor
    struct Printer {
        std::ostream& os;
        symbol_table_t& st;
    };

    // TODO: define "double term_t::operator()(state_t&) const" using visitor pattern (call EvaluationVisitor)

    Printer& operator<<(Printer& p, const term_t&) {
        p.os << "(a+b)"; // FIXME: mockup, use visitor pattern to implement properly
        return p;
    }
    Printer& operator<<(Printer& os, const expr_t& t) { return os << *t.term; }

}

using namespace calculator;

TEST_CASE("plus")
{
    auto sys = symbol_table_t{};
    auto a = sys.var("a", 2);
    auto b = sys.var("b", 3);
    auto s = sys.state();
    auto os = std::ostringstream();
    auto p = Printer{os, sys};

    auto sum = a + b;

    SUBCASE("print")
    {
        p << sum; // pretty-print the sum
        CHECK(os.str() == "(a+b)");
    }

    SUBCASE("evaluate")
    {
        auto value = sum(s); // evaluate the sum at state s
        CHECK(value == 5);
    }
}