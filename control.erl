-module(control).
-import(lights, [set/3, display/1, clear/0]).
-export([pulse_start/0, pulse_stop/0, pulse_loop/1]).

pulse_loop(Yellow) ->
    lights:set(0, Yellow, 0),
    receive
        stop -> lights:clear()
    after
        1000 -> pulse_loop(1-Yellow)
    end.

pulse_start() ->
    case whereis(pulser) of
        undefined ->
            register(pulser, spawn_link(?MODULE, pulse_loop, [1])),
            ok;
        _ -> ok
    end.

pulse_stop() ->
    pulser ! stop.
    