add_rules("mode.debug", "mode.release")
set_languages("c++17")
add_requires("gtest", {configs = {main = true}})
if is_plat("windows") then -- for MSVC
    add_cxflags("/utf-8")
    add_ldflags("/subsystem:console")
end

target("tests")
    set_kind("binary")
    add_files("sources/*.cpp")
    add_files("tests/*.cpp")
    add_packages("gtest")
