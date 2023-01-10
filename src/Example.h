#pragma once
// Copied from godot-cpp/test/src and modified.

#include "godot_cpp/classes/control.hpp"
#include "godot_cpp/classes/global_constants.hpp"
#include "godot_cpp/classes/viewport.hpp"
#include "godot_cpp/core/binder_common.hpp"

class ExampleRef : public godot::RefCounted
{
    GDCLASS( ExampleRef, RefCounted )

private:
    static int instance_count;
    static int last_id;

    int id;

protected:
    static void _bind_methods();

public:
    ExampleRef();
    ~ExampleRef();

    int get_id();
};

class ExampleMin : public godot::Control
{
    GDCLASS( ExampleMin, Control )

protected:
    static void _bind_methods()
    {
    }
};

class Example : public godot::Control
{
    GDCLASS( Example, godot::Control )

protected:
    static void _bind_methods();

    void _notification( int p_what );
    bool _set( const godot::StringName &p_name, const godot::Variant &p_value );
    bool _get( const godot::StringName &p_name, godot::Variant &r_ret ) const;
    void _get_property_list( godot::List<godot::PropertyInfo> *p_list ) const;
    bool _property_can_revert( const godot::StringName &p_name ) const;
    bool _property_get_revert( const godot::StringName &p_name, godot::Variant &r_property ) const;

    godot::String _to_string() const;

private:
    godot::Vector2 custom_position;
    godot::Vector3 property_from_list;
    godot::Vector2 dprop[3];

public:
    // Constants.
    enum Constants
    {
        FIRST,
        ANSWER_TO_EVERYTHING = 42,
    };

    enum
    {
        CONSTANT_WITHOUT_ENUM = 314,
    };

    Example();
    ~Example() override;

    // Functions.
    void simple_func();
    void simple_const_func() const;
    godot::String return_something( const godot::String &base );
    godot::Viewport *return_something_const() const;
    godot::Ref<ExampleRef> return_empty_ref() const;
    ExampleRef *return_extended_ref() const;
    godot::Ref<ExampleRef> extended_ref_checks( godot::Ref<ExampleRef> p_ref ) const;
    godot::Variant varargs_func( const godot::Variant **args, GDExtensionInt arg_count,
                                 GDExtensionCallError &error );
    int varargs_func_nv( const godot::Variant **args, GDExtensionInt arg_count,
                         GDExtensionCallError &error );
    void varargs_func_void( const godot::Variant **args, GDExtensionInt arg_count,
                            GDExtensionCallError &error );

    void emit_custom_signal( const godot::String &name, int value );
    int def_args( int p_a = 100, int p_b = 200 );

    godot::Array test_array() const;
    void test_tarray_arg( const godot::TypedArray<int64_t> &p_array );
    godot::TypedArray<godot::Vector2> test_tarray() const;
    godot::Dictionary test_dictionary() const;
    Example *test_node_argument( Example *p_node ) const;

    // Property.
    void set_custom_position( const godot::Vector2 &pos );
    godot::Vector2 get_custom_position() const;
    godot::Vector4 get_v4() const;

    // Static method.
    static int test_static( int p_a, int p_b );
    static void test_static2();

    // Virtual function override (no need to bind manually).
    virtual bool _has_point( const godot::Vector2 &point ) const override;
};

VARIANT_ENUM_CAST( Example, Constants )

class ExampleVirtual : public godot::Object
{
    GDCLASS( ExampleVirtual, godot::Object )

protected:
    static void _bind_methods()
    {
    }
};

class ExampleAbstract : public godot::Object
{
    GDCLASS( ExampleAbstract, godot::Object )

protected:
    static void _bind_methods()
    {
    }
};
