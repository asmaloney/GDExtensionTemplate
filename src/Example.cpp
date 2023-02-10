// Copied from godot-cpp/test/src and modified.

#include "godot_cpp/classes/global_constants.hpp"
#include "godot_cpp/classes/label.hpp"
#include "godot_cpp/core/class_db.hpp"
#include "godot_cpp/variant/utility_functions.hpp"

#include "Example.h"

// Used to mark unused parameters to indicate intent and suppress warnings.
#define UNUSED( expr ) (void)( expr )

namespace
{
    constexpr int MAGIC_NUMBER = 42;
}

//// ExampleRef

int ExampleRef::sInstanceCount = 0;
int ExampleRef::sLastID = 0;

ExampleRef::ExampleRef()
{
    mID = ++sLastID;
    sInstanceCount++;

    godot::UtilityFunctions::print(
        "ExampleRef ", godot::itos( mID ),
        " created, current instance count: ", godot::itos( sInstanceCount ) );
}

ExampleRef::~ExampleRef()
{
    sInstanceCount--;
    godot::UtilityFunctions::print(
        "ExampleRef ", godot::itos( mID ),
        " destroyed, current instance count: ", godot::itos( sInstanceCount ) );
}

int ExampleRef::getID() const
{
    return mID;
}

void ExampleRef::_bind_methods()
{
    godot::ClassDB::bind_method( godot::D_METHOD( "get_id" ), &ExampleRef::getID );
}

//// ExampleMin

void ExampleMin::_bind_methods()
{
}

//// Example

Example::Example()
{
    godot::UtilityFunctions::print( "Constructor." );
}

Example::~Example()
{
    godot::UtilityFunctions::print( "Destructor." );
}

// Methods.
void Example::simpleFunc()
{
    godot::UtilityFunctions::print( "  Simple func called." );
}

void Example::simpleConstFunc() const
{
    godot::UtilityFunctions::print( "  Simple const func called." );
}

godot::String Example::returnSomething( const godot::String &inBase )
{
    godot::UtilityFunctions::print( "  Return something called." );

    return inBase;
}

godot::Viewport *Example::returnSomethingConst() const
{
    godot::UtilityFunctions::print( "  Return something const called." );

    if ( is_inside_tree() )
    {
        godot::Viewport *result = get_viewport();

        return result;
    }

    return nullptr;
}

godot::Ref<ExampleRef> Example::returnEmptyRef() const
{
    godot::Ref<ExampleRef> ref;
    return ref;
}

ExampleRef *Example::returnExtendedRef() const
{
    // You can instance and return a refcounted object like this, but keep in mind that refcounting
    // starts with the returned object and it will be destroyed when all references are destroyed.
    // If you store this pointer you run the risk of having a pointer to a destroyed object.
    return memnew( ExampleRef() );
}

godot::Ref<ExampleRef> Example::extendedRefChecks( godot::Ref<ExampleRef> inRef ) const
{
    // This is the preferred way of instancing and returning a refcounted object:
    godot::Ref<ExampleRef> ref;
    ref.instantiate();

    godot::UtilityFunctions::print(
        "  Example ref checks called with value: ", inRef->get_instance_id(),
        ", returning value: ", ref->get_instance_id() );

    return ref;
}

godot::Variant Example::varargsFunc( const godot::Variant **inArgs, GDExtensionInt inArgCount,
                                     GDExtensionCallError &outError )
{
    UNUSED( inArgs );
    UNUSED( outError );

    godot::UtilityFunctions::print( "  Varargs (Variant return) called with ",
                                    godot::String::num_int64( inArgCount ), " arguments" );

    return inArgCount;
}

int Example::varargsFuncNonVoidReturn( const godot::Variant **inArgs, GDExtensionInt inArgCount,
                                       GDExtensionCallError &outError )
{
    UNUSED( inArgs );
    UNUSED( outError );

    godot::UtilityFunctions::print( "  Varargs (int return) called with ",
                                    godot::String::num_int64( inArgCount ), " arguments" );

    return MAGIC_NUMBER;
}

void Example::varargsFuncVoidReturn( const godot::Variant **inArgs, GDExtensionInt inArgCount,
                                     GDExtensionCallError &outError )
{
    UNUSED( inArgs );
    UNUSED( outError );

    godot::UtilityFunctions::print( "  Varargs (no return) called with ",
                                    godot::String::num_int64( inArgCount ), " arguments" );
}

void Example::emitCustomSignal( const godot::String &inName, int inValue )
{
    emit_signal( "custom_signal", inName, inValue );
}

int Example::defArgs( int inA, int inB ) const
{
    return inA + inB;
}

godot::Array Example::testArray() const
{
    godot::Array arr;

    arr.resize( 2 );
    arr[0] = godot::Variant( 1 );
    arr[1] = godot::Variant( 2 );

    return arr;
}

void Example::testTypedArrayArg( const godot::TypedArray<int64_t> &inArray )
{
    for ( int i = 0; i < inArray.size(); ++i )
    {
        godot::UtilityFunctions::print( inArray[i] );
    }
}

godot::TypedArray<godot::Vector2> Example::testTypedArray() const
{
    godot::TypedArray<godot::Vector2> arr;

    arr.resize( 2 );
    arr[0] = godot::Vector2( 1, 2 );
    arr[1] = godot::Vector2( 2, 3 );

    return arr;
}

godot::Dictionary Example::testDictionary() const
{
    godot::Dictionary dict;

    dict["hello"] = "world";
    dict["foo"] = "bar";

    return dict;
}

Example *Example::testNodeArgument( Example *inNode ) const
{
    // This should use godot::String::num_uint64(), but it is currently broken:
    //  https://github.com/godotengine/godot-cpp/issues/1014
    godot::UtilityFunctions::print(
        "  Test node argument called with ",
        ( inNode != nullptr )
            ? godot::String::num_int64( static_cast<int64_t>( inNode->get_instance_id() ) )
            : "null" );
    return inNode;
}

godot::String Example::testStringOps() const
{
    godot::String s = godot::String( "A" );
    s += "B";
    s += "C";
    s += char32_t( 0x010E );
    s = s + "E";

    return s;
}

int Example::testVectorOps() const
{
    godot::PackedInt32Array arr;
    arr.push_back( 10 );
    arr.push_back( 20 );
    arr.push_back( 30 );
    arr.push_back( 45 );

    int ret = 0;
    for ( const int32_t &E : arr )
    {
        ret += E;
    }

    return ret;
}

godot::BitField<Example::Flags> Example::testBitfield( godot::BitField<Flags> inFlags )
{
    godot::UtilityFunctions::print( "  Got BitField: ", godot::String::num_int64( inFlags ) );
    return inFlags;
}

// Properties.
void Example::setCustomPosition( const godot::Vector2 &inPos )
{
    mCustomPosition = inPos;
}

godot::Vector2 Example::getCustomPosition() const
{
    return mCustomPosition;
}

godot::Vector4 Example::getV4() const
{
    return { 1.2f, 3.4f, 5.6f, 7.8f };
}

// Static methods
int Example::testStatic( int inA, int inB )
{
    return inA + inB;
}

void Example::testStatic2()
{
    godot::UtilityFunctions::print( "  void static" );
}

// Virtual function override.
bool Example::_has_point( const godot::Vector2 &inPoint ) const
{
    auto *label = godot::Control::get_node<godot::Label>( "Label" );

    label->set_text( "Got point: " + godot::Variant( inPoint ).stringify() );

    return false;
}

void Example::_bind_methods()
{
    // Methods.
    godot::ClassDB::bind_method( godot::D_METHOD( "simple_func" ), &Example::simpleFunc );
    godot::ClassDB::bind_method( godot::D_METHOD( "simple_const_func" ),
                                 &Example::simpleConstFunc );
    godot::ClassDB::bind_method( godot::D_METHOD( "return_something" ), &Example::returnSomething );
    godot::ClassDB::bind_method( godot::D_METHOD( "return_something_const" ),
                                 &Example::returnSomethingConst );
    godot::ClassDB::bind_method( godot::D_METHOD( "return_empty_ref" ), &Example::returnEmptyRef );
    godot::ClassDB::bind_method( godot::D_METHOD( "return_extended_ref" ),
                                 &Example::returnExtendedRef );
    godot::ClassDB::bind_method( godot::D_METHOD( "extended_ref_checks", "ref" ),
                                 &Example::extendedRefChecks );

    godot::ClassDB::bind_method( godot::D_METHOD( "test_array" ), &Example::testArray );
    godot::ClassDB::bind_method( godot::D_METHOD( "test_tarray_arg", "array" ),
                                 &Example::testTypedArrayArg );
    godot::ClassDB::bind_method( godot::D_METHOD( "test_tarray" ), &Example::testTypedArray );
    godot::ClassDB::bind_method( godot::D_METHOD( "test_dictionary" ), &Example::testDictionary );
    godot::ClassDB::bind_method( godot::D_METHOD( "test_node_argument" ),
                                 &Example::testNodeArgument );
    godot::ClassDB::bind_method( godot::D_METHOD( "test_string_ops" ), &Example::testStringOps );
    godot::ClassDB::bind_method( godot::D_METHOD( "test_vector_ops" ), &Example::testVectorOps );

    godot::ClassDB::bind_method( godot::D_METHOD( "test_bitfield", "flags" ),
                                 &Example::testBitfield );

    godot::ClassDB::bind_method( godot::D_METHOD( "def_args", "a", "b" ), &Example::defArgs,
                                 DEFVAL( 100 ), DEFVAL( 200 ) );

    godot::ClassDB::bind_static_method( "Example", godot::D_METHOD( "test_static", "a", "b" ),
                                        &Example::testStatic );
    godot::ClassDB::bind_static_method( "Example", godot::D_METHOD( "test_static2" ),
                                        &Example::testStatic2 );

    {
        godot::MethodInfo mi;
        mi.arguments.emplace_back( godot::Variant::STRING, "some_argument" );
        mi.name = "varargs_func";

        godot::ClassDB::bind_vararg_method( godot::METHOD_FLAGS_DEFAULT, "varargs_func",
                                            &Example::varargsFunc, mi );
    }

    {
        godot::MethodInfo mi;
        mi.arguments.emplace_back( godot::Variant::STRING, "some_argument" );
        mi.name = "varargs_func_nv";

        godot::ClassDB::bind_vararg_method( godot::METHOD_FLAGS_DEFAULT, "varargs_func_nv",
                                            &Example::varargsFuncNonVoidReturn, mi );
    }

    {
        godot::MethodInfo mi;
        mi.arguments.emplace_back( godot::Variant::STRING, "some_argument" );
        mi.name = "varargs_func_void";

        godot::ClassDB::bind_vararg_method( godot::METHOD_FLAGS_DEFAULT, "varargs_func_void",
                                            &Example::varargsFuncVoidReturn, mi );
    }

    // Properties.
    ADD_GROUP( "Test group", "group_" );
    ADD_SUBGROUP( "Test subgroup", "group_subgroup_" );

    godot::ClassDB::bind_method( godot::D_METHOD( "get_custom_position" ),
                                 &Example::getCustomPosition );
    godot::ClassDB::bind_method( godot::D_METHOD( "get_v4" ), &Example::getV4 );
    godot::ClassDB::bind_method( godot::D_METHOD( "set_custom_position", "position" ),
                                 &Example::setCustomPosition );
    ADD_PROPERTY( godot::PropertyInfo( godot::Variant::VECTOR2, "group_subgroup_custom_position" ),
                  "set_custom_position", "get_custom_position" );

    // Signals.
    ADD_SIGNAL( godot::MethodInfo( "custom_signal",
                                   godot::PropertyInfo( godot::Variant::STRING, "name" ),
                                   godot::PropertyInfo( godot::Variant::INT, "value" ) ) );
    godot::ClassDB::bind_method( godot::D_METHOD( "emit_custom_signal", "name", "value" ),
                                 &Example::emitCustomSignal );

    // Constants.
    BIND_ENUM_CONSTANT( FIRST )
    BIND_ENUM_CONSTANT( ANSWER_TO_EVERYTHING )

    BIND_BITFIELD_FLAG( FLAG_ONE );
    BIND_BITFIELD_FLAG( FLAG_TWO );

    BIND_CONSTANT( CONSTANT_WITHOUT_ENUM );
    BIND_ENUM_CONSTANT( OUTSIDE_OF_CLASS );
}

void Example::_notification( int inWhat )
{
    godot::UtilityFunctions::print( "Notification: ", godot::String::num( inWhat ) );
}

bool Example::_set( const godot::StringName &inName, const godot::Variant &inValue )
{
    godot::String name = inName;

    if ( name.begins_with( "dproperty" ) )
    {
        int64_t index = name.get_slicec( '_', 1 ).to_int();
        mDProp[index] = inValue;

        return true;
    }

    if ( name == "property_from_list" )
    {
        mPropertyFromList = inValue;

        return true;
    }

    return false;
}

bool Example::_get( const godot::StringName &inName, godot::Variant &outReturn ) const
{
    godot::String name = inName;

    if ( name.begins_with( "dproperty" ) )
    {
        int64_t index = name.get_slicec( '_', 1 ).to_int();
        outReturn = mDProp[index];

        return true;
    }

    if ( name == "property_from_list" )
    {
        outReturn = mPropertyFromList;

        return true;
    }

    return false;
}

void Example::_get_property_list( godot::List<godot::PropertyInfo> *outList ) const
{
    outList->push_back( godot::PropertyInfo( godot::Variant::VECTOR3, "property_from_list" ) );

    for ( int i = 0; i < 3; ++i )
    {
        outList->push_back(
            godot::PropertyInfo( godot::Variant::VECTOR2, "dproperty_" + godot::itos( i ) ) );
    }
}

bool Example::_property_can_revert( const godot::StringName &inName ) const
{
    if ( inName == godot::StringName( "property_from_list" ) &&
         mPropertyFromList != godot::Vector3( MAGIC_NUMBER, MAGIC_NUMBER, MAGIC_NUMBER ) )
    {
        return true;
    }

    return false;
};

bool Example::_property_get_revert( const godot::StringName &inName,
                                    godot::Variant &outProperty ) const
{
    if ( inName == godot::StringName( "property_from_list" ) )
    {
        outProperty = godot::Vector3( MAGIC_NUMBER, MAGIC_NUMBER, MAGIC_NUMBER );

        return true;
    }

    return false;
};

godot::String Example::_to_string() const
{
    return "[ GDExtension::Example <--> Instance ID:" + godot::uitos( get_instance_id() ) + " ]";
}

//// ExampleVirtual

void ExampleVirtual::_bind_methods()
{
}

//// ExampleAbstract

void ExampleAbstract::_bind_methods()
{
}
