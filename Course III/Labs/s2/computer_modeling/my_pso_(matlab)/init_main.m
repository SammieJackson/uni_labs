% All parameters' definition, problem initialization, main program body

clc;
clear;
close all;
% addpath('C:\Users\Admin\Downloads\my_pso');

%% Parameter init

problem.Function = @(x) f(x);  % target function

% x = [1 2];
% y = f(x)

problem.dims = 2;        % number of dimensions
problem.min_val = -10;   % lower bound 
problem.max_val = 10;    % upper bound

params.iters = 900;        % maximum number of iterations
params.swarm = 50;          % population (swarm size)
params.inert = 1;           % intertia coefficient
params.inert_damp = 0.99;   % damping ratio of inertia coefficient
params.phi_p = 2;           % personal acceleration coefficient - phi_p
params.phi_g = 2;           % social acceleration coefficient - phi_g
params.show_iters = true;   % flag for showing iteration info
params.normalization_coeff = 1;

params.inert_final = 0.04; % 10^(-10); % final value for inertia for linear damping

%% for normalization - so that phi_p and _g do not influence speed that much
%{
param_k = 0.5;  % another parameter - should be between 0 and 1
phi = params.phi_p + params.phi_g;
params.normalization_coeff = 2*param_k / abs(2 - phi - sqrt(phi^2 - 4*phi));
%}

%% Calling PSO

out = pso(problem, params);

BestSol = out.best_val;
BestPos = out.best_pos;
BestValsHist = out.best_vals_hist;
% BestPosHist = out.best_pos_hist;

AllHist = out.all_hist;

%% Results

%{
% Best function value plot
figure;
% plot(BestValsHist, 'LineWidth', 2);
semilogy(BestValsHist, 'LineWidth', 2);
xlabel('Iteration');
ylabel('Best Value');
grid on;
%}

%{
particle_num = 1;
% t = 1:params.iters;
% x = AllHist(1, 1).pos(1)
% y = AllHist(particle_num, t).pos(2);
% comet(x,y);
%}

%{
particle_num = 1;
x = zeros(1,params.iters);
y = zeros(1,params.iters);
for t = 1:params.iters
    x(t) = AllHist(particle_num,t).pos(1);
    y(t) = AllHist(particle_num,t).pos(2);
end
comet(x,y);
%}

%% Draw trajectory of a single particle
%{
% grid_nodes = 1000;
x0 = linspace(problem.min_val, problem.max_val);
y0 = linspace(problem.min_val, problem.max_val);
[x0,y0] = meshgrid(x0,y0);
% z0 = f([x0 y0]);
z0 = x0.^2 + y0.^2;
% z0 = x0.^2 - 10*cos(x0.*2*pi) + y0.^2 - 10*cos(y0.*2*pi); z0 = z0 + 10*2;
%{
% z0 = zeros(1, numel(x0));
z0 = linspace(problem.min_val, problem.max_val);
for i = 1:numel(x0)
    z0(i) = - x0(i)*sin(sqrt( x0(i) )) - y0(i)*sin(sqrt( y0(i) ));
end
%}
hold on
mesh(x0,y0,z0)
particle_num = 1;
x = zeros(1,params.iters);
y = zeros(1,params.iters);
z = zeros(1,params.iters);
for t = 1:params.iters
    x(t) = AllHist(particle_num,t).pos(1);
    y(t) = AllHist(particle_num,t).pos(2);
    z(t) = AllHist(particle_num,t).func;
end
h = animatedline;
for t = 1:params.iters
    addpoints(h,x(t),y(t),z(t));
    pause(.1)
    drawnow
end
%}

%% Attempt to draw trajectories of multiple particles
%{
number_of_particles = 5;
x = zeros(number_of_particles,params.iters);
y = zeros(number_of_particles,params.iters);
for i = 1:number_of_particles
    for t = 1:params.iters
        x(i,t) = AllHist(i,t).pos(1);
        y(i,t) = AllHist(i,t).pos(2);
    end
end
h0 = animatedline();
h = repmat(h0, 1, number_of_particles);
for t = 1:params.iters
    for i = 1:number_of_particles
        addpoints(h(i),x(i,t),y(i,t));
    end
    pause(.1)
    drawnow
end
%}

%% Attempt to animate the movement of particles
%%{
dot_size = 5;
color = 'k';
ub = 10^(-30);
lb = -ub;

f = figure;
% x0 = linspace(problem.min_val, problem.max_val);
% y0 = linspace(problem.min_val, problem.max_val);
x0 = linspace(lb, ub);
y0 = linspace(lb, ub);
[x0,y0] = meshgrid(x0,y0);
% z0 = f([x0 y0]);
z0 = x0.^2 + y0.^2;
% z0 = x0.^2 - 10*cos(x0.*2*pi) + y0.^2 - 10*cos(y0.*2*pi); z0 = z0 + 10*2;
hold on
mesh(x0,y0,z0)

number_of_particles = 10;
swarm = params.swarm;
if number_of_particles > swarm
    number_of_particles = swarm;
end
iters = params.iters;
particles_x = zeros(1,number_of_particles);
particles_y = zeros(1,number_of_particles);
%{
s = scatter(particles_x, particles_y, dot_size, color, 'filled');
s.XDataSource = 'particles_x';
s.YDataSource = 'particles_y';
xlim([lb ub])
ylim([lb ub])
%}
%plot(particles_x, particles_y, 'x')
last_iteration = 500;
for t = 1:iters
    for i = 1:number_of_particles
        particles_x(i) = AllHist(i,t).pos(1);
        particles_y(i) = AllHist(i,t).pos(2);
    end
    if t < last_iteration
        clf
        plot(particles_x, particles_y, 'x')
        title(num2str(t));
        axis([-5 5 -5 5]);
        % xlim([lb ub])
        % ylim([lb ub])
        % refreshdata
        % drawnow
        pause(0.05)
    end
end
%}
