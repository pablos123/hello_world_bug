#include <EXTERN.h>
#include <perl.h>

static PerlInterpreter *my_perl;

int main(int argc, char **argv, char **env) {

    char *embedding[] = { "", "-e", "0", NULL };

    PERL_SYS_INIT3(&argc, &argv, &env);
    my_perl = perl_alloc();
    perl_construct(my_perl);

    perl_parse(my_perl, NULL, 3, embedding, NULL);
    PL_exit_flags |= PERL_EXIT_DESTRUCT_END;
    perl_run(my_perl);

    eval_pv("print \"Hello World!\n\"", TRUE);

    perl_destruct(my_perl);
    perl_free(my_perl);
    PERL_SYS_TERM();

    exit(EXIT_SUCCESS);
}
