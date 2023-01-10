// Copied from godot-cpp/test/src and modified.

#include "godot_cpp/classes/global_constants.hpp"
#include "godot_cpp/classes/label.hpp"
#include "godot_cpp/core/class_db.hpp"
#include "godot_cpp/variant/utility_functions.hpp"

#include "Example.h"

int ExampleRef::instance_count = 0;
int ExampleRef::last_id = 0;

int ExampleRef::get_id()
{
    return id;
}

void ExampleRef::_bind_methods()
{
    godot::ClassDB::bind_method( godot::D_METHOD( "get_id" ), &ExampleRef::get_id );
}

ExampleRef::ExampleRef()
{
    id = ++last_id;
    instance_count++;

    godot::UtilityFunctions::print(
        "ExampleRef ", godot::itos( id ),
        " created, current instance count: ", godot::itos( instance_count ) );
}

ExampleRef::~ExampleRef()
{
    instance_count--;
    godot::UtilityFunctions::print(
        "ExampleRef ", godot::itos( id ),
        " destroyed, current instance count: ", godot::itos( instance_count ) );
}

int Example::test_static( int p_a, int p_b )
{
    return p_a + p_b;
}

void Example::test_static2()
{
    godot::UtilityFunctions::print( "  void static" );
}

int Example::def_args( int p_a, int p_b )
{
    return p_a + p_b;
}

void Example::_notification( int p_what )
{
    godot::UtilityFunctions::print( "Notification: ", godot::String::num( p_what ) );
}

bool Example::_set( const godot::StringName &p_name, const godot::Variant &p_value )
{
    godot::String name = p_name;

    if ( name.begins_with( "dproperty" ) )
    {
        int64_t index = name.get_slicec( '_', 1 ).to_int();
        dprop[index] = p_value;

        return true;
    }

    if ( name == "property_from_list" )
    {
        property_from_list = p_value;

        return true;
    }

    return false;
}

bool Example::_get( const godot::StringName &p_name, godot::Variant &r_ret ) const
{
    godot::String name = p_name;

    if ( name.begins_with( "dproperty" ) )
    {
        int64_t index = name.get_slicec( '_', 1 ).to_int();
        r_ret = dprop[index];

        return true;
    }

    if ( name == "property_from_list" )
    {
        r_ret = property_from_list;

        return true;
    }

    return false;
}

godot::String Example::_to_string() const
{
    return "[ GDExtension::Example <--> Instance ID:" + godot::uitos( get_instance_id() ) + " ]";
}

void Example::_get_property_list( godot::List<godot::PropertyInfo> *p_list ) const
{
    p_list->push_back( godot::PropertyInfo( godot::Variant::VECTOR3, "property_from_list" ) );

    for ( int i = 0; i < 3; ++i )
    {
        p_list->push_back(
            godot::PropertyInfo( godot::Variant::VECTOR2, "dproperty_" + godot::itos( i ) ) );
    }
}

bool Example::_property_can_revert( const godot::StringName &p_name ) const
{
    if ( p_name == godot::StringName( "property_from_list" ) &&
         property_from_list != godot::Vector3( 42, 42, 42 ) )
    {
        return true;
    }

    return false;
};

bool Example::_property_get_revert( const godot::StringName &p_name,
                                    godot::Variant &r_property ) const
{
    if ( p_name == godot::StringName( "property_from_list" ) )
    {
        r_property = godot::Vector3( 42, 42, 42 );

        return true;
    }

    return false;
};

void Example::_bind_methods()
{
    // Methods.
    godot::ClassDB::bind_method( godot::D_METHOD( "simple_func" ), &Example::simple_func );
    godot::ClassDB::bind_method( godot::D_METHOD( "simple_const_func" ),
                                 &Example::simple_const_func );
    godot::ClassDB::bind_method( godot::D_METHOD( "return_something" ),
                                 &Example::return_something );
    godot::ClassDB::bind_method( godot::D_METHOD( "return_something_const" ),
                                 &Example::return_something_const );
    godot::ClassDB::bind_method( godot::D_METHOD( "return_empty_ref" ),
                                 &Example::return_empty_ref );
    godot::ClassDB::bind_method( godot::D_METHOD( "return_extended_ref" ),
                                 &Example::return_extended_ref );
    godot::ClassDB::bind_method( godot::D_METHOD( "extended_ref_checks", "ref" ),
                                 &Example::extended_ref_checks );

    godot::ClassDB::bind_method( godot::D_METHOD( "test_array" ), &Example::test_array );
    godot::ClassDB::bind_method( godot::D_METHOD( "test_tarray_arg", "array" ),
                                 &Example::test_tarray_arg );
    godot::ClassDB::bind_method( godot::D_METHOD( "test_tarray" ), &Example::test_tarray );
    godot::ClassDB::bind_method( godot::D_METHOD( "test_dictionary" ), &Example::test_dictionary );
    godot::ClassDB::bind_method( godot::D_METHOD( "test_node_argument" ),
                                 &Example::test_node_argument );

    godot::ClassDB::bind_method( godot::D_METHOD( "def_args", "a", "b" ), &Example::def_args,
                                 DEFVAL( 100 ), DEFVAL( 200 ) );

    godot::ClassDB::bind_static_method( "Example", godot::D_METHOD( "test_static", "a", "b" ),
                                        &Example::test_static );
    godot::ClassDB::bind_static_method( "Example", godot::D_METHOD( "test_static2" ),
                                        &Example::test_static2 );

    {
        godot::MethodInfo mi;
        mi.arguments.emplace_back( godot::Variant::STRING, "some_argument" );
        mi.name = "varargs_func";

        godot::ClassDB::bind_vararg_method( godot::METHOD_FLAGS_DEFAULT, "varargs_func",
                                            &Example::varargs_func, mi );
    }

    {
        godot::MethodInfo mi;
        mi.arguments.emplace_back( godot::Variant::STRING, "some_argument" );
        mi.name = "varargs_func_nv";

        godot::ClassDB::bind_vararg_method( godot::METHOD_FLAGS_DEFAULT, "varargs_func_nv",
                                            &Example::varargs_func_nv, mi );
    }

    {
        godot::MethodInfo mi;
        mi.arguments.emplace_back( godot::Variant::STRING, "some_argument" );
        mi.name = "varargs_func_void";

        godot::ClassDB::bind_vararg_method( godot::METHOD_FLAGS_DEFAULT, "varargs_func_void",
                                            &Example::varargs_func_void, mi );
    }

    // Properties.
    ADD_GROUP( "Test group", "group_" );
    ADD_SUBGROUP( "Test subgroup", "group_subgroup_" );

    godot::ClassDB::bind_method( godot::D_METHOD( "get_custom_position" ),
                                 &Example::get_custom_position );
    godot::ClassDB::bind_method( godot::D_METHOD( "get_v4" ), &Example::get_v4 );
    godot::ClassDB::bind_method( godot::D_METHOD( "set_custom_position", "position" ),
                                 &Example::set_custom_position );
    ADD_PROPERTY( godot::PropertyInfo( godot::Variant::VECTOR2, "group_subgroup_custom_position" ),
                  "set_custom_position", "get_custom_position" );

    // Signals.
    ADD_SIGNAL( godot::MethodInfo( "custom_signal",
                                   godot::PropertyInfo( godot::Variant::STRING, "name" ),
                                   godot::PropertyInfo( godot::Variant::INT, "value" ) ) );
    godot::ClassDB::bind_method( godot::D_METHOD( "emit_custom_signal", "name", "value" ),
                                 &Example::emit_custom_signal );

    // Constants.
    BIND_ENUM_CONSTANT( FIRST )
    BIND_ENUM_CONSTANT( ANSWER_TO_EVERYTHING )

    BIND_CONSTANT( CONSTANT_WITHOUT_ENUM )
}

Example::Example()
{
    godot::UtilityFunctions::print( "Constructor." );
}

Example::~Example()
{
    godot::UtilityFunctions::print( "Destructor." );
}

// Methods.
void Example::simple_func()
{
    godot::UtilityFunctions::print( "  Simple func called." );
}

void Example::simple_const_func() const
{
    godot::UtilityFunctions::print( "  Simple const func called." );
}

godot::String Example::return_something( const godot::String &base )
{
    godot::UtilityFunctions::print( "  Return something called." );

    return base;
}

godot::Viewport *Example::return_something_const() const
{
    godot::UtilityFunctions::print( "  Return something const called." );

    if ( is_inside_tree() )
    {
        godot::Viewport *result = get_viewport();

        return result;
    }

    return nullptr;
}

godot::Ref<ExampleRef> Example::return_empty_ref() const
{
    godot::Ref<ExampleRef> ref;
    return ref;
}

ExampleRef *Example::return_extended_ref() const
{
    // You can instance and return a refcounted object like this, but keep in mind that refcounting
    // starts with the returned object and it will be destroyed when all references are destroyed.
    // If you store this pointer you run the risk of having a pointer to a destroyed object.
    return memnew( ExampleRef() );
}

godot::Ref<ExampleRef> Example::extended_ref_checks( godot::Ref<ExampleRef> p_ref ) const
{
    // This is the preferred way of instancing and returning a refcounted object:
    godot::Ref<ExampleRef> ref;
    ref.instantiate();

    godot::UtilityFunctions::print(
        "  Example ref checks called with value: ", p_ref->get_instance_id(),
        ", returning value: ", ref->get_instance_id() );

    return ref;
}

godot::Variant Example::varargs_func( const godot::Variant ** /*args*/, GDExtensionInt arg_count,
                                      GDExtensionCallError & /*error*/ )
{
    godot::UtilityFunctions::print( "  Varargs (Variant return) called with ",
                                    godot::String::num( static_cast<double>( arg_count ) ),
                                    " arguments" );

    return arg_count;
}

int Example::varargs_func_nv( const godot::Variant ** /*args*/, GDExtensionInt arg_count,
                              GDExtensionCallError & /*error*/ )
{
    godot::UtilityFunctions::print( "  Varargs (int return) called with ",
                                    godot::String::num( static_cast<double>( arg_count ) ),
                                    " arguments" );

    return 42;
}

void Example::varargs_func_void( const godot::Variant ** /*args*/, GDExtensionInt arg_count,
                                 GDExtensionCallError & /*error*/ )
{
    godot::UtilityFunctions::print( "  Varargs (no return) called with ",
                                    godot::String::num( static_cast<double>( arg_count ) ),
                                    " arguments" );
}

void Example::emit_custom_signal( const godot::String &name, int value )
{
    emit_signal( "custom_signal", name, value );
}

godot::Array Example::test_array() const
{
    godot::Array arr;

    arr.resize( 2 );
    arr[0] = godot::Variant( 1 );
    arr[1] = godot::Variant( 2 );

    return arr;
}

void Example::test_tarray_arg( const godot::TypedArray<int64_t> &p_array )
{
    for ( int i = 0; i < p_array.size(); ++i )
    {
        godot::UtilityFunctions::print( p_array[i] );
    }
}

godot::TypedArray<godot::Vector2> Example::test_tarray() const
{
    godot::TypedArray<godot::Vector2> arr;

    arr.resize( 2 );
    arr[0] = godot::Vector2( 1, 2 );
    arr[1] = godot::Vector2( 2, 3 );

    return arr;
}

godot::Dictionary Example::test_dictionary() const
{
    godot::Dictionary dict;

    dict["hello"] = "world";
    dict["foo"] = "bar";

    return dict;
}

Example *Example::test_node_argument( Example *p_node ) const
{
    godot::UtilityFunctions::print( "  Test node argument called with ",
                                    p_node ? godot::String::num( p_node->get_instance_id() )
                                           : "null" );
    return p_node;
}

// Properties.
void Example::set_custom_position( const godot::Vector2 &pos )
{
    custom_position = pos;
}

godot::Vector2 Example::get_custom_position() const
{
    return custom_position;
}

godot::Vector4 Example::get_v4() const
{
    return { 1.2f, 3.4f, 5.6f, 7.8f };
}

// Virtual function override.
bool Example::_has_point( const godot::Vector2 &point ) const
{
    godot::Label *label = godot::Control::get_node<godot::Label>( "Label" );

    label->set_text( "Got point: " + godot::Variant( point ).stringify() );

    return false;
}
