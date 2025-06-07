#include <linux/module.h>
#include <linux/export-internal.h>
#include <linux/compiler.h>

MODULE_INFO(name, KBUILD_MODNAME);

__visible struct module __this_module
__section(".gnu.linkonce.this_module") = {
	.name = KBUILD_MODNAME,
	.init = init_module,
#ifdef CONFIG_MODULE_UNLOAD
	.exit = cleanup_module,
#endif
	.arch = MODULE_ARCH_INIT,
};

KSYMTAB_FUNC(GetSystemLibrary, "", "");
KSYMTAB_FUNC(SystemAdd, "", "");
KSYMTAB_FUNC(SystemStart, "", "");
KSYMTAB_FUNC(SystemEnd, "", "");

SYMBOL_CRC(GetSystemLibrary, 0x3d5abfde, "");
SYMBOL_CRC(SystemAdd, 0x187a9fea, "");
SYMBOL_CRC(SystemStart, 0x66574f9e, "");
SYMBOL_CRC(SystemEnd, 0xe763bcbe, "");

static const struct modversion_info ____versions[]
__used __section("__versions") = {
	{ 0xbdfb6dbb, "__fentry__" },
	{ 0x65487097, "__x86_indirect_thunk_rax" },
	{ 0x5b8239ca, "__x86_return_thunk" },
	{ 0xe2d5255a, "strcmp" },
	{ 0x1e7bbcb3, "kernel_restart" },
	{ 0x7696f8c7, "__list_add_valid_or_report" },
	{ 0x037cd00f, "module_layout" },
};

MODULE_INFO(depends, "");

