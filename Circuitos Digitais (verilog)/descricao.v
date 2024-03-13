module me (
input   eck,
input   er,
input   es,
input   eena,
input   up,
input   ini,
output  [6:0] sq);


wire [2:0] ea;
wire [2:0] pe;
wire out, out_certo;
wire nini;
not(nini, ini);
and(out_certo, eena, out);


freq_div contador (.eck(eck),.er(er),.es(es),.eena(eena),.j(out));


cc_pe proximo_estado (.ea(ea), .up(up), .pe(pe));


reg3 meu_registrador_querido (.d(pe), .ck(eck), .reset(er),
.set(es), .enable(out_certo), .q(ea), .nini(nini));


cc_saida xololo (.ea(ea), .s(sq));
   
endmodule




module cc_pe (
input   [2:0] ea,
input up,
output  [2:0] pe);


wire nup;
wire nea[2:0];
wire w0, w1, w2, w3, w4, w5, w6, w7;


not(nup, up);
not(nea[2], ea[2]);
not(nea[1], ea[1]);
not(nea[0], ea[0]);


and(w0, nup, ea[1], ea[0]);
and(w1, up, ea[1], nea[0]);
and(w2, nup, nea[1], nea[0]);
and(w3, up, nea[1], ea[0]);


and(w4, nup, ea[2], ea[0]);
and(w5, up, ea[2], nea[0]);
and(w6, up, ea[1], ea[0]);
and(w7, nup, ea[1], nea[0]);


or(pe[2], w0, w1, w2, w3, nea[2]);
or(pe[1], w4, w5, w6, w7);
buf(pe[0], nea[0]);


endmodule




module cc_saida (
input   [2:0] ea,
output  [6:0] s);


wire nea0,nea1,nea2;
wire w0,w1,w2,w3,w4,w5;
not(nea2, ea[2]);
not(nea1, ea[1]);
not(nea0, ea[0]);


and(w0, ea[2], ea[1]);
and(w1, nea1, ea[0]);


and(w2, ea[2], nea0);
and(w3, ea[1], ea[0]);


and(w4, nea0, ea[2]);
and(w5, ea[1], ea[0]);


or(s[6], w4, w5);
or(s[5], ea[0], nea2, nea1);
buf(s[4], 1'b1);
or(s[3], w2, w3);
and(s[2], ea[2], ea[1], ea[0]);
or(s[1], w0, w1);
or(s[0], ea[0], ea[2]);


endmodule




module reg3 (
input   [2:0] d,
input   ck,
input   reset,
input   set,
input   enable,
output  [2:0] q,
input   nini);


dffrse armazena_ea2(
        .din(d[2]),
        .dout(q[2]),
        .clk(ck),
        .en(enable),
        .set(nini),
        .rst(reset));    


dffrse armazena_ea1(
        .din(d[1]),
        .dout(q[1]),
        .clk(ck),
        .en(enable),
        .set(set),
        .rst(nini));
       
dffrse armazena_ea0(
        .din(d[0]),
        .dout(q[0]),
        .clk(ck),
        .en(enable),
        .set(set),
        .rst(nini));    
   
endmodule




module dffrse(din, dout, clk, en, set, rst);
    input din, clk, en, set, rst;
    output reg dout;


    always@(posedge clk, posedge rst) begin
        if(rst)
            dout <= 1'b0;
        else if(set)
            dout <= 1'b1;
        else if(en)
            dout <= din;
        else
            dout <= dout;
    end
endmodule




//divisor
module freq_div (
input   eck,
input   er,
input   es,
input   eena,
output  j);


wire [1:0] ea;
wire [1:0] pe;


cc_pe2 proximo_estado (.ea(ea), .pe(pe));


reg4 meu_registrador_querido (.d(pe), .ck(eck), .reset(er),
.set(es), .enable(eena), .q(ea));


cc_saida2 xololo (.ea(ea), .s(j));
   
endmodule




module cc_pe2 (
input   [1:0] ea,
output  [1:0] pe);
 
buf(pe[1], ea[0]);
nor(pe[0], ea[1], ea[0]);


endmodule




module cc_saida2 (
input   [1:0] ea,
output  s);


buf(s, ea[0]);


endmodule




module reg4 (
input   [1:0] d,
input   ck,
input   reset,
input   set,
input   enable,
output  [1:0] q);


dffrse armazena_ea1(
        .din(d[1]),
        .dout(q[1]),
        .clk(ck),
        .en(enable),
        .set(set),
        .rst(reset));
       
dffrse armazena_ea0(
        .din(d[0]),
        .dout(q[0]),
        .clk(ck),
        .en(enable),
        .set(set),
        .rst(reset));                                              
endmodule




module dffrse2(din, dout, clk, en, set, rst);
    input din, clk, en, set, rst;
    output reg dout;


    always@(posedge clk, posedge rst) begin
        if(rst)
            dout <= 1'b0;
        else if(set)
            dout <= 1'b1;
        else if(en)
            dout <= din;
        else
            dout <= dout;
    end
endmodule
