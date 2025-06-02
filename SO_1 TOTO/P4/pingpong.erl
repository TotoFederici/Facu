-module(pingpong).
-export([pong/0, ping/0, play/0, ping_aux/1, pong_aux/0]).

pong_aux() ->
    process_flag(trap_exit, true),
    pong().

pong() ->
    receive
        {0, PidPing} ->
            io:fwrite("Final Prog!~n"),
            PidPing ! {fin, self()},
            pongok;
        {N, PidPing} ->
            io:fwrite("Pong! Recv ~p~n",[N]),
            PidPing ! { (N-1), self()},
            pong();
        {'EXIT', From, Reason} -> 
            io:fwrite("Ping is DEAD, Pong va a revivirlo, info: ~p~n",[{'EXIT', From, Reason}]),
            PidPing = spawn(?MODULE, ping_aux, [self()]),
            PidPing ! {10, self()},
            pong()
    end.

ping_aux(PidPong) ->
    link(PidPong),
    ping().

ping() ->
    receive
        {fin, _PidPong} ->
            io:fwrite("Final Ping!~n"),
            pingok;
        {3, _PidPong} -> 
            error(lala);
        {N, PidPong} ->
            io:fwrite("Ping!"),
            PidPong ! {N, self()},
            ping()
    end.
            
play() ->
    PidPong = spawn(?MODULE, pong_aux, []),
    PidPing = spawn(?MODULE, ping_aux, [PidPong]),
    PidPong ! {10, PidPing},
    playok.