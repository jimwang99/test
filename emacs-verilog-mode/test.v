module test (/*AUTOARG*/
   // Outputs
   z,
   // Inputs
   clk, rstn, a, b
   );

input   wire    clk, rstn;
input   wire    [DATA_WIDTH-1:0]    a, b;
output  wire    [DATA_WIDTH-1:0]    z;

sub sub_u (/*AUTOINST*/
	   // Outputs
	   .z				(z[DATA_WIDTH-1:0]),
	   // Inputs
	   .clk				(clk),
	   .rstn			(rstn),
	   .a				(a[DATA_WIDTH-1:0]),
	   .b				(b[DATA_WIDTH-1:0]));

endmodule

// Local Variables:
// verilog-library-directories:("." "sub")
// End:
