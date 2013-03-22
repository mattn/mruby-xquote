#include <mruby.h>
#include <mruby/string.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>

static mrb_value
mrb_xquote(mrb_state *mrb, mrb_value self) {
  FILE* fp;
  char* cmd;
  char buf[BUFSIZ];
  mrb_value out;
  int ai;

  mrb_get_args(mrb, "z", &cmd);
  fp = popen(cmd, "r");
  if (!fp) {
    mrb_raise(mrb, E_RUNTIME_ERROR, strerror(errno));
  }
  out = mrb_str_new_cstr(mrb, "");
  ai = mrb_gc_arena_save(mrb);
  while (fgets(buf, sizeof(buf), fp) != NULL) {
    mrb_str_cat2(mrb, out, buf);
    mrb_gc_arena_restore(mrb, ai);
  }
  pclose(fp);

  return out;
}

/*********************************************************
 * register
 *********************************************************/

void
mrb_mruby_xquote_gem_init(mrb_state* mrb) {
  mrb_define_class_method(mrb, mrb->kernel_module, "`", mrb_xquote, ARGS_REQ(1));
}

void
mrb_mruby_xquote_gem_final(mrb_state* mrb) {
}

/* vim:set et ts=2 sts=2 sw=2 tw=0: */
