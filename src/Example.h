#pragma once
// Copied from godot-cpp/test/src and modified.

#include "godot_cpp/classes/control.hpp"
#include "godot_cpp/classes/global_constants.hpp"
#include "godot_cpp/classes/tile_map.hpp"
#include "godot_cpp/classes/tile_set.hpp"
#include "godot_cpp/classes/viewport.hpp"
#include "godot_cpp/core/binder_common.hpp"
#include "godot_cpp/variant/variant.hpp"

class ExampleRef : public godot::RefCounted
{
    GDCLASS( ExampleRef, RefCounted )

public:
    ExampleRef();
    ~ExampleRef() override;

    void setId( int inID );
    int getID() const;

    bool wasPostInitialized() const
    {
        return mPostInitialized;
    }

protected:
    static void _bind_methods();

    void _notification( int inWhat );

private:
    static int sInstanceCount;
    static int sLastID;

    int mID;
    bool mPostInitialized = false;
};

class ExampleMin : public godot::Control
{
    GDCLASS( ExampleMin, Control )

protected:
    static void _bind_methods();
};

class Example : public godot::Control
{
    GDCLASS( Example, godot::Control )

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

    enum Flags
    {
        FLAG_ONE = 1,
        FLAG_TWO = 2,
    };

    Example();
    ~Example() override;

    // Functions.
    void simpleFunc();
    void simpleConstFunc() const;
    godot::String returnSomething( const godot::String &inBase );
    godot::Viewport *returnSomethingConst() const;
    godot::Ref<ExampleRef> returnEmptyRef() const;
    ExampleRef *returnExtendedRef() const;
    godot::Ref<ExampleRef> extendedRefChecks( godot::Ref<ExampleRef> inRef ) const;
    godot::Variant varargsFunc( const godot::Variant **inArgs, GDExtensionInt inArgCount,
                                GDExtensionCallError &outError );
    int varargsFuncNonVoidReturn( const godot::Variant **inArgs, GDExtensionInt inArgCount,
                                  GDExtensionCallError &outError );
    void varargsFuncVoidReturn( const godot::Variant **inArgs, GDExtensionInt inArgCount,
                                GDExtensionCallError &outError );

    void emitCustomSignal( const godot::String &inName, int inValue );
    int defArgs( int inA = 100, int inB = 200 ) const;

    godot::Array testArray() const;
    void testTypedArrayArg( const godot::TypedArray<int64_t> &inArray );
    godot::TypedArray<godot::Vector2> testTypedArray() const;
    godot::Dictionary testDictionary() const;
    Example *testNodeArgument( Example *inNode ) const;
    godot::String testStringOps() const;
    godot::String testStrUtility() const;
    bool testStringIsFortyTwo( const godot::String &inString ) const;
    godot::String testStringResize( godot::String ioString ) const;
    int testVectorOps() const;

    bool testObjectCastToNode( godot::Object *inObject ) const;
    bool testObjectCastToControl( godot::Object *inObject ) const;
    bool testObjectCastToExample( godot::Object *inObject ) const;

    godot::Vector2i testVariantVector2iConversion( const godot::Variant &inVariant ) const;
    int testVariantIntConversion( const godot::Variant &inVariant ) const;
    float testVariantFloatConversion( const godot::Variant &inVariant ) const;
    godot::Variant testVariantCall( godot::Variant inVariant );
    godot::Variant testVariantIterator( const godot::Variant &inVariant );

    void testAddChild( godot::Node *inNode );
    void testSetTileset( godot::TileMap *inTilemap,
                         const godot::Ref<godot::TileSet> &inTileset ) const;

    godot::Callable testCallableMP();
    godot::Callable testCallableMPRet();
    godot::Callable testCallableMPRetC() const;
    godot::Callable testCallableMPStatic() const;
    godot::Callable testCallableMPStaticRet() const;
    godot::Callable testCustomCallable() const;

    void callableBind();

    void unboundMethod1( godot::Object *inObject, godot::String inString, int inInt );
    godot::String unboundMethod2( godot::Object *inObject, godot::String inString, int inInt );
    godot::String unboundMethod3( godot::Object *inObject, godot::String inString,
                                  int inInt ) const;
    static void unboundStaticMethod1( Example *inObject, godot::String inString, int inInt );
    static godot::String unboundStaticMethod2( godot::Object *inObject, godot::String inString,
                                               int inInt );

    godot::BitField<Flags> testBitfield( godot::BitField<Flags> inFlags );

    // RPC
    void testRPC( int inValue );
    void testSendRPC( int inValue );
    int returnLastRPCArg();

    // Property
    void setCustomPosition( const godot::Vector2 &inPos );
    godot::Vector2 getCustomPosition() const;
    godot::Vector4 getV4() const;

    bool testPostInitialize() const;

    // Static method.
    static int testStatic( int inA, int inB );
    static void testStatic2();

    // Virtual function override (no need to bind manually).
    virtual bool _has_point( const godot::Vector2 &inPoint ) const override;

protected:
    static void _bind_methods();

    void _notification( int inWhat );
    bool _set( const godot::StringName &inName, const godot::Variant &inValue );
    bool _get( const godot::StringName &inName, godot::Variant &outReturn ) const;
    void _get_property_list( godot::List<godot::PropertyInfo> *outList ) const;
    bool _property_can_revert( const godot::StringName &inName ) const;
    bool _property_get_revert( const godot::StringName &inName, godot::Variant &outProperty ) const;
    void _validate_property( godot::PropertyInfo &inProperty ) const;

    godot::String _to_string() const;

private:
    godot::Vector2 mCustomPosition;
    godot::Vector3 mPropertyFromList;
    godot::Vector2 mDProp[3];

    int mLastRPCArg = 0;
};

VARIANT_ENUM_CAST( Example::Constants );
VARIANT_BITFIELD_CAST( Example::Flags );

enum EnumWithoutClass
{
    OUTSIDE_OF_CLASS = 512
};
VARIANT_ENUM_CAST( EnumWithoutClass );

class ExampleVirtual : public godot::Object
{
    GDCLASS( ExampleVirtual, godot::Object )

protected:
    static void _bind_methods();
};

class ExampleAbstract : public godot::Object
{
    GDCLASS( ExampleAbstract, godot::Object )

protected:
    static void _bind_methods();
};
