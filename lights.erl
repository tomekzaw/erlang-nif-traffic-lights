-module(lights).
-export([set/3, display/1, clear/0]).
-on_load(init/0).

init() ->
    ok = erlang:load_nif("./lights_nif", 0).

set(_red, _yellow, _green) ->
    {error, nif_library_not_loaded}.

display(_colors) ->
    {error, nif_library_not_loaded}.

clear() ->
    {error, nif_library_not_loaded}.
