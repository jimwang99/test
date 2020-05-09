module sub (/*AUTOARG*/
   // Outputs
   z,
   // Inputs
   clk, rstn, a, b
   );

input   wire    clk, rstn;
input   wire    [DATA_WIDTH-1:0]    a, b;
output  wire    [DATA_WIDTH-1:0]    z;

endmodule
