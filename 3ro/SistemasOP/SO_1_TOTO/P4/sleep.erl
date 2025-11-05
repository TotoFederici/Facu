-module(sleep).
-export([sleep/1, init/1]).

sleep(N) ->
    receive
    after
        N -> ok
    end.

init(N) ->
    io:fwrite("hola\n"),
    sleep(N),
    io:fwrite("chau\n").