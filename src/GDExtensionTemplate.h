#pragma once
// SPDX-License-Identifier: Unlicense

#include "godot_cpp/classes/object.hpp"

namespace godot
{
    class ClassDB;
};

class GDExtensionTemplate : public godot::Object
{
    GDCLASS( GDExtensionTemplate, godot::Object )

public:
    static godot::String version();
    static godot::String godotCPPVersion();

private:
    static void _bind_methods();
};
