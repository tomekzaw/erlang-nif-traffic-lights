#include <erl_nif.h>
#include <stdbool.h>

extern int load();
extern int upgrade();
extern void unload();
extern void set();
extern void clear();

static ERL_NIF_TERM set_nif(ErlNifEnv* env, int argc, const ERL_NIF_TERM argv[]) {
    int red, yellow, green;
    if (!enif_get_int(env, argv[0], &red) || !enif_get_int(env, argv[1], &yellow) || !enif_get_int(env, argv[2], &green)) {
	    return enif_make_badarg(env);
    }
    set(!!red, !!yellow, !!green);
    return enif_make_atom(env, "ok");
}

static ERL_NIF_TERM display_nif(ErlNifEnv* env, int argc, const ERL_NIF_TERM argv[]) {
    ERL_NIF_TERM list = argv[0], head, tail;
    if (!enif_is_list(env, list)) {
        return enif_make_badarg(env);
    }
    ERL_NIF_TERM atoms[3] = {
        enif_make_atom(env, "red"),
        enif_make_atom(env, "yellow"),
        enif_make_atom(env, "green")
    };
    int colors[3] = {0};
    while (!enif_is_empty_list(env, list)) {
        if (!enif_get_list_cell(env, list, &head, &tail) || !enif_is_atom(env, head)) {
	        return enif_make_badarg(env);
        }
        bool atom_found = false;
        size_t i;
        for (i = 0; i < sizeof(atoms) / sizeof(*atoms); ++i) {
            if (enif_is_identical(head, atoms[i])) {
                colors[i] = 1;
                atom_found = true;
                break;
            }
        }
        if (!atom_found) {
            return enif_make_badarg(env);
        }
        list = tail;
    }
    set(colors[0], colors[1], colors[2]);
    return enif_make_atom(env, "ok");
}

static ERL_NIF_TERM clear_nif(ErlNifEnv* env, int argc, const ERL_NIF_TERM argv[]) {
    clear();
    return enif_make_atom(env, "ok");
}

static ErlNifFunc nif_funcs[] = {
    {"set", 3, set_nif},
    {"display", 1, display_nif},
    {"clear", 0, clear_nif}
};

ERL_NIF_INIT(lights, nif_funcs, load, NULL, upgrade, unload)
