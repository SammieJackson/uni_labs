
%% Plot phase portrait for first equilibrium point (first system)

function plot_ph_port_1_2()

    clc;
    clear;
    clear all;

    top = 1.2; bot = .3; left = .3; right = 1.1;
    step=.1;
    time = 1;
    with_vectorfield = 1;

    nodes = 40;
    x_field_step = (right - left)/nodes;
    y_field_step = (top - bot)/nodes;

    % х - густ попул жертви
    % у - хижака

    eps1 = 3;   % розмнож жерт без хиж
    eps2 = 4;   % заг жерт без хиж
    gam1 = 4;   % зменш жерт за на€в хиж
    gam2 = 6;   % прир б≥омас хиж за на€в жерт

    init1 = [0; 0] % перша точка р≥вноваги - вимиранн€
    init2 = [eps2/gam2; eps1/gam1] % друга стац≥онарна точка - коливанн€

    sys_no_interspec = @(t,x) [eps1*x(1) - gam1*x(1)*x(2); gam2*x(1)*x(2) - eps2*x(2)];

    if with_vectorfield
       vectorfield(sys_no_interspec,left:x_field_step:right,bot:y_field_step:top);
    end
    hold on

    for x0=left:step:right
        for y0=bot:step:top
            [ts,xs] = ode45(sys_no_interspec,[0 time],[x0 y0]);
           plot(xs(:,1),xs(:,2))
        end
    end
    for x0=left:step:right
        for y0=bot:step:top
            [ts,xs] = ode45(sys_no_interspec,[0 -time],[x0 y0]);
            plot(xs(:,1),xs(:,2))
        end
    end
    hold off
    axis([left right bot top])
    fsize=15;
    %{
    set(gca,ТXTickТ,-3:1:3,ТFontSizeТ,fsize)
    set(gca,ТYTickТ,-3:1:3,ТFontSizeТ,fsize)
    xlabel(Тx(t)Т,ТFontSizeТ,fsize)
    ylabel(Тy(t)Т,ТFontSizeТ,fsize)
    %}
    hold off

end