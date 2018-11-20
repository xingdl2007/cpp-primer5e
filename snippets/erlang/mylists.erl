-module(mylists).
-export([sum/1]).

sum([H|L]) -> H + sum(L);
sum([]) -> 0.