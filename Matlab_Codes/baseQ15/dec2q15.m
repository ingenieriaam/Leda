%%%%%%%%%%% author: Szymon Leja 2008-01-11
function [y]=dec2q15(x,form)


option = {'mode' , 'roundmode', 'overflowmode', 'format'}; 
value   = {'fixed', 'ceil'     , 'saturate'    ,  [16 15]}; 
q = quantizer( option, value ) ;

if form=='bin'
    y=num2bin(q,x);
end;

if form=='hex'
    y=num2hex(q,x);
end;

end

% 
% Description	
% y = dec2q15( x , form )
% 
% Function that works with any decimal value (beacuse of saturation using). Available representation of Q15 format are binary or hexadecimal.
% 
% Input arguments of function: 
% x - decimal integer 
% form - form - dependent on representation of input argument (hexadecimal or binary) take 'hex' or 'bin'
% 
% Valu of function: 
% y - its hexadecimal or binary representation stored in a MATLAB string
% 
% EXAMPLE: 
% >> dec2q15(0.125,'hex')
% 
% ans =
% 
% 1000
% 
% >> dec2q15(0.125,'bin')
% 
% ans =
% 
% 0001000000000000
% 
% >> dec2q15(-0.775,'hex')
% 
% ans =
% 
% 9ccd
% 
% >> dec2q15(-0.775,'bin')
% 
% ans =
% 
% 1001110011001101