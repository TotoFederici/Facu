-module(broadcaster).
-export([iniciar/0, broadcast/1, registrar/0, finalizar/0]).
-export([loopBroadcast/1, ack/0]).
-export([test/0, client/0]).

ack() ->
    receive
        servOK -> ok;
        servERR -> error
    end.

iniciar() -> 
    Pid = spawn(?MODULE, loopBroadcast, [[]]),
    register(server, Pid),
    ok.

finalizar() ->
    server ! {fin, self()},
    ack().

broadcast(Msg) ->
    server ! {env, Msg, self()},
    ack().

registrar() ->
    server ! {reg, self()},
    ack().

loopBroadcast(St) ->
    receive
        {fin, PidClient} -> 
            PidClient ! servOK,
            ok;
        {env, Msg, PidClient} ->
            PidClient ! servOK,
            lists:foreach( fun(X) -> X ! Msg end, St),
            loopBroadcast(St);
        {reg, Pid} ->
            Pid ! servOK,
            io:fwrite("client ~p registered  ~n", [Pid]),
            loopBroadcast([Pid | St])
    end.

client() ->
    io:fwrite("clien ~p registering... ~n", [self()]),
    registrar(),
    receive
        Msg -> io:fwrite("client ~p receive ~p ~n", [self(), Msg])
    end.

test() ->
    broadcaster:iniciar(),
    spawn(?MODULE, client, []),
    spawn(?MODULE, client, []),
    timer:sleep(1000),
    broadcast(hola).