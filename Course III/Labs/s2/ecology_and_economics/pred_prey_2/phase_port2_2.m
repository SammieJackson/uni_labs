
%% Plot phase portrait for second equilibrium point (second system)

function plot_ph_port_2_2()

    clc;
    clear;
    clear all;

    top = 1; bot = -1; left = 2; right = 4;
    step=.25;
    time = 1;
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

    % +
    beta1 = 1;  % �����-��� ���� ����

    init1 = [0; 0] % ����� ����� ��������
    init2 = [eps1/beta1; 0] % ����� ����������� �����
    init3 = [eps2/gam2; (eps1*gam2 - beta1*eps2)/(gam1*gam2)] % ����� ����������� �����

    sys_with_interspec = @(t,x) [eps1*x(1) - gam1*x(1)*x(2) - beta1*x(1)^2; gam2*x(1)*x(2) - eps2*x(2)];

    if with_vectorfield
       vectorfield(sys_with_interspec, left:x_field_step:right, bot:y_field_step:top);
    end
    hold on

    for x0=left:step:right
        for y0=bot:step:top
            [ts,xs] = ode45(sys_with_interspec,[0 time],[x0 y0]);
           plot(xs(:,1),xs(:,2))
        end
    end
    for x0=left:step:right
        for y0=bot:step:top
            [ts,xs] = ode45(sys_with_interspec,[0 -time],[x0 y0]);
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