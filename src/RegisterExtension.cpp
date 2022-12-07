// Copied from godot-cpp/test/src and modified.

#include "godot/gdnative_interface.h"
#include "godot_cpp/core/class_db.hpp"
#include "godot_cpp/core/defs.hpp"
#include "godot_cpp/godot.hpp"

#include "Example.h"

namespace
{
   void initializeExtension( godot::ModuleInitializationLevel p_level )
   {
      if ( p_level != godot::MODULE_INITIALIZATION_LEVEL_SCENE )
      {
         return;
      }

      godot::ClassDB::register_class<ExampleRef>();
      godot::ClassDB::register_class<ExampleMin>();
      godot::ClassDB::register_class<Example>();
      godot::ClassDB::register_class<ExampleVirtual>( true );
      godot::ClassDB::register_abstract_class<ExampleAbstract>();
   }

   void uninitializeExtension( godot::ModuleInitializationLevel p_level )
   {
      if ( p_level != godot::MODULE_INITIALIZATION_LEVEL_SCENE )
      {
         return;
      }
   }
}

extern "C"
{
   // The name of this function must match the "entry_symbol" in templates/template.gdextension.in
   GDNativeBool GDN_EXPORT GDExtensionInit( const GDNativeInterface *p_interface,
                                            GDNativeExtensionClassLibraryPtr p_library,
                                            GDNativeInitialization *r_initialization )
   {
      godot::GDExtensionBinding::InitObject init_obj( p_interface, p_library, r_initialization );

      init_obj.register_initializer( initializeExtension );
      init_obj.register_terminator( uninitializeExtension );
      init_obj.set_minimum_library_initialization_level( godot::MODULE_INITIALIZATION_LEVEL_SCENE );

      return init_obj.init();
   }
}
