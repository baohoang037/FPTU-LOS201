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



static const struct modversion_info ____versions[]
__used __section("__versions") = {
	{ 0xc714db12, "single_open" },
	{ 0x5fe49b2b, "seq_printf" },
	{ 0xbd03ed67, "__ref_stack_chk_guard" },
	{ 0x5cb46e6d, "validate_usercopy_range" },
	{ 0xa61fd7aa, "__check_object_size" },
	{ 0x092a35a2, "_copy_from_user" },
	{ 0x41495f0d, "strim" },
	{ 0xd09b06f5, "kstrtoint" },
	{ 0x90a48d82, "__ubsan_handle_out_of_bounds" },
	{ 0xd272d446, "__stack_chk_fail" },
	{ 0x40a621c5, "snprintf" },
	{ 0x092a35a2, "_copy_to_user" },
	{ 0x26772f20, "remove_proc_entry" },
	{ 0x155e60e3, "misc_deregister" },
	{ 0xe290afe8, "seq_read" },
	{ 0xce9b2870, "seq_lseek" },
	{ 0x6f7437b5, "single_release" },
	{ 0xd272d446, "__fentry__" },
	{ 0xe98a2697, "misc_register" },
	{ 0xe8213e80, "_printk" },
	{ 0xdef8136e, "proc_create" },
	{ 0xd272d446, "__x86_return_thunk" },
	{ 0xe9196a28, "module_layout" },
};

static const u32 ____version_ext_crcs[]
__used __section("__version_ext_crcs") = {
	0xc714db12,
	0x5fe49b2b,
	0xbd03ed67,
	0x5cb46e6d,
	0xa61fd7aa,
	0x092a35a2,
	0x41495f0d,
	0xd09b06f5,
	0x90a48d82,
	0xd272d446,
	0x40a621c5,
	0x092a35a2,
	0x26772f20,
	0x155e60e3,
	0xe290afe8,
	0xce9b2870,
	0x6f7437b5,
	0xd272d446,
	0xe98a2697,
	0xe8213e80,
	0xdef8136e,
	0xd272d446,
	0xe9196a28,
};
static const char ____version_ext_names[]
__used __section("__version_ext_names") =
	"single_open\0"
	"seq_printf\0"
	"__ref_stack_chk_guard\0"
	"validate_usercopy_range\0"
	"__check_object_size\0"
	"_copy_from_user\0"
	"strim\0"
	"kstrtoint\0"
	"__ubsan_handle_out_of_bounds\0"
	"__stack_chk_fail\0"
	"snprintf\0"
	"_copy_to_user\0"
	"remove_proc_entry\0"
	"misc_deregister\0"
	"seq_read\0"
	"seq_lseek\0"
	"single_release\0"
	"__fentry__\0"
	"misc_register\0"
	"_printk\0"
	"proc_create\0"
	"__x86_return_thunk\0"
	"module_layout\0"
;

MODULE_INFO(depends, "");


MODULE_INFO(srcversion, "1F6D0B4AD5EB6A7DFEFD6C8");
