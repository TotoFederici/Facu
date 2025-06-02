-module(exception).
-export([divide/2, test/0, arroja/0, dummy/0]).

divide(M,N) ->
    case catch (M / N) of
        {'EXIT', {badarith, Stack}} -> io:fwrite("DIVIDISTE POR CERO!!!. STACK: ~p ~n", [Stack]);
        Res -> Res
    end.

dummy() ->
    throw(die).

arroja() ->
    case catch dummy() of
        die -> io:fwrite("MORISTE!!!!!!~n")
    end.


test() ->
    arroja(),
    ok.