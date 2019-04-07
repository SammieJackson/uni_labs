


%% Plot phase portrait for first equilibrium point (first system)
function plot_ph_port_1_1()

    clc;
    clear;
    clear all;

    top = .5; bot = -.5; left = -.5; right = .5;
    step=.1;
    time = .3;
    with_vectorfield = 1;

    nodes = 40;
    x_field_step = (right - left)/nodes;
    y_field_step = (top - bot)/nodes;

    % � - ���� ����� ������
    % � - ������

    eps1 = 3;   % ������� ���� ��� ���
    eps2 = 4;   % ��� ���� ��� ���
    gam1 = 4;   % ����� ���� �� ���� ���
    gam2 = 6;   % ���� ����� ��� �� ���� ����

    init1 = [0; 0] % ����� ����� �������� - ���������
    init2 = [eps2/gam2; eps1/gam1] % ����� ����������� ����� - ���������

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
    set(gca,�XTick�,-3:1:3,�FontSize�,fsize)
    set(gca,�YTick�,-3:1:3,�FontSize�,fsize)
    xlabel(�x(t)�,�FontSize�,fsize)
    ylabel(�y(t)�,�FontSize�,fsize)
    %}
    hold off

end