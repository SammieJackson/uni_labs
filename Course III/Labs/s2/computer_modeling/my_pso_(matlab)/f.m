%{
function z = f(x)
    txt = sprintf('\n Hello!');
    disp(txt);
    z = x + 1;
end

%%
%{
x = [1 2 3];
y = targ_func(x);
disp(y)
%}
%}

%% Target function init

%%{
% Squared function (distance to origin)
function f = f(x)
    f = sum(x.^2);
end
%}

%{
% Rastrigin function
function f = f(x)
    n = numel(x);
    f = sum(x.^2 - 10*cos(x.*2*pi));
    f = f + 10*n;
end
%}

%{
% Shvefel function
function f = f(x)
    n = numel(x);
    f = 0;
    for i = 1:n
        f = f - x(i) * sin(sqrt( x(i) ));
    end
end
%}
