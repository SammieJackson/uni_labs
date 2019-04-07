% pso function definition

function res = pso(problem, params)
    %% Problem Definiton

    func = problem.Function;  % target function
    dims = problem.dims;        % number of dimensions
    min_val = problem.min_val;   % lower bound 
    max_val = problem.max_val;    % upper bound
    varsize = [1 dims];
    
    %% Parameters
    
    iters = params.iters;        % maximum number of iterations
    N = params.swarm;          % population (swarm size)
    w = params.inert;           % intertia coefficient
    w_damp = params.inert_damp;   % damping ratio of inertia coefficient
    phi_p = params.phi_p;           % personal acceleration coefficient - phi_p
    phi_g = params.phi_g;           % social acceleration coefficient - phi_g
    show_iters = params.show_iters;   % flag for showing iteration info
    X = params.normalization_coeff;
    
    max_vel = 0.2*(max_val-min_val);
    min_vel = -max_vel;
    
    w_linear_damp_step = (w - params.inert_final) / iters % damping step for linearly regressing inertia
    
    %% Initialization
    
    % swarm_coords_dims = (swarm, dims);
    
    % The Particle Template
    % particle = [];
    particle.pos = []; % zeros(1,dims);
    particle.vel = []; % zeros(1,dims);
    particle.func = [];
    particle.best.pos = []; % zeros(1,dims);
    particle.best.func = [];
    
    % population state array
    swarm = repmat(particle, N, 1);
    
    global_best.func = inf;
    % global_best_pos = []; % zeros(1,dims);
    
    
    %% Initialize particles
    
    swarm_ind = 1:N;
    for i = swarm_ind
        swarm(i).pos = unifrnd(min_val, max_val, varsize); % unifrnd(swarm(i).pos+min_val, max_val);
        swarm(i).vel = unifrnd(min_vel, max_vel, varsize); % unifrnd(swarm(i).vel+min_vel, max_vel);
        swarm(i).best.pos = swarm(i).pos;
        swarm(i).func = func(swarm(i).pos);
        % fprintf( ['\n', num2str(swarm(i).func)] );
        swarm(i).best.func = swarm(i).func;
        
        % disp(swarm(i));   % print initial particle stats
        
        if swarm(i).best.func < global_best.func
            global_best = swarm(i).best;
        end
    end
    
    best_vals = zeros(iters,1);
    % best_positions = repmat(global_best.pos, iters);
    
    % tmp_pos = zeros(1,dims);
    particle0.pos = unifrnd(min_val, max_val, varsize);
    particle0.func = 0;
    particle0.func = func(particle0.pos);
    hist = repmat(particle0, N, iters); % history of all particle stats
    
    %% Iterations
    
    for i = 1:iters
       
        for j = 1:N
           
            r_p = rand(varsize); % unifrnd(0,1,1,N); % direction of personal acceleration
            r_g = rand(varsize); % unifrnd(0,1,1,N); % direction of personal acceleration
            swarm(j).vel = ( w * swarm(j).vel + ...
                phi_p * r_p .* (swarm(j).best.pos - swarm(j).pos) + ...
                phi_g * r_g .* (global_best.pos - swarm(j).pos) ) * X ;
            
            swarm(j).vel = max(swarm(j).vel, min_vel);
            swarm(j).vel = min(swarm(j).vel, max_vel);
            
            swarm(j).pos = swarm(j).pos + swarm(j).vel;
            
            if any(swarm(j).pos > max_val) | any(swarm(j).pos < min_val)
                swarm(j).pos = global_best.pos;
            end
            
            swarm(j).func = func(swarm(j).pos);
            
            hist(j,i).pos = swarm(j).pos;
            hist(j,i).func = swarm(j).func;
            
            if swarm(j).func < swarm(j).best.func
                swarm(j).best.func = swarm(j).func;
                swarm(j).best.pos = swarm(j).pos;
                
                if swarm(j).best.func < global_best.func
                    global_best = swarm(j).best;
                    % fprintf( ['\n', num2str(swarm(j).best_func)] );
                end
            end
             
        end % end of swarm cycle
        
        % size(best_vals(i));
        % size(global_best.func);
        best_vals(i) = global_best.func;
        % best_positions = [best_positions, global_best.pos];
        % best_positions(i) = global_best.pos;
        
        if show_iters
            fprintf([ '\nIteration ' num2str(i) ':\n\t Best Cost = ' num2str(best_vals(i))]); % '\n\t Best Pos: ' num2str(best_positions(i,:)) ]);
        end
        
        % w = update_inertia(w,i,"Geom",w_damp); % update inertia - geometrical sequence
        w = update_inertia(w,i,"Linear",w_linear_damp_step); % update inertia - linear sequence
    end
    
    % res.swarm_fin = swarm;
    res.best_val = global_best.func;
    res.best_pos = global_best.pos;
    res.best_vals_hist = best_vals;
    % res.best_pos_hist = best_positions;
    res.all_hist = hist;
    
end

function res = update_inertia(tmp_inert, iteration_num, option_num, params)
    switch option_num
        case "Geom"
            res = tmp_inert * params;
        case "Linear"
            res = tmp_inert - params;
    end
end