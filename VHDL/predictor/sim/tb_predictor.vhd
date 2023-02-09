----------------------------------------------------------------------------------
-- Name: Wesley Grignani
-- Laboratory of Embedded and Distributed Systems (LEDS) - UNIVALI
----------------------------------------------------------------------------------
-- Testbench file for predictor block
----------------------------------------------------------------------------------
library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
use IEEE.NUMERIC_STD.ALL;
use std.textio.all;
use IEEE.std_logic_textio.all;
library work;
use work.ccsds123_b2_package.all;

entity tb_predictor is
-- empty
end tb_predictor;

architecture Behavioral of tb_predictor is

component top is
  port ( i_clk          : in  std_logic; 
         i_rst          : in  std_logic;
         i_start        : in  std_logic;
         i_t            : in  std_logic_vector(7 downto 0);
         i_z            : in  std_logic_vector(2 downto 0);
         i_sample       : in  std_logic_vector(SAMPLE_SIZE-1 downto 0);
         i_neighboor    : in  std_logic_vector(SAMPLE_SIZE-1 downto 0);
         o_mapped       : out std_logic_vector(SAMPLE_SIZE-1 downto 0));
end component;

constant c_CLK_PERIOD : time := 10 ns;
signal w_clk, w_rst, w_start : std_logic := '0';
signal w_t : std_logic_vector(7 downto 0) := (others => '0');
signal w_z : std_logic_vector(2 downto 0) := (others => '0');
signal w_sample, w_neighboor, w_mapped : std_logic_vector(SAMPLE_SIZE-1 downto 0) := (others => '0');
file input_buff : text;

begin

  -- device under test 
  u_DUV : top
    port map (i_clk        => w_clk,
              i_rst        => w_rst,
              i_start      => w_start,
              i_t          => w_t,
              i_z          => w_z,
              i_sample     => w_sample,
              i_neighboor  => w_neighboor, 
              o_mapped     => w_mapped);
              
  -- clock process 
   p_CLK : process
   begin
     w_clk <= '0';
     wait for c_CLK_PERIOD/2;
     w_clk <= '1';
     wait for c_CLK_PERIOD/2;
   end process p_CLK;
         
         
   p_text : process
   variable read_col_from_input_buff : line;
   variable val_col0, val_col1, val_col2, val_col3, test : integer;
   variable v_space : character;
   begin
     test := 0;
     file_open(input_buff, "tb_data.txt", READ_MODE);
     wait for c_CLK_PERIOD*7;
     while not endfile(input_buff) loop
       readline(input_buff, read_col_from_input_buff);
       read(read_col_from_input_buff, val_col0);  -- i_t
       read(read_col_from_input_buff, v_space);
       read(read_col_from_input_buff, val_col1);  -- i_z
       read(read_col_from_input_buff, v_space);
       read(read_col_from_input_buff, val_col2);  -- i_sample
       read(read_col_from_input_buff, v_space);
       read(read_col_from_input_buff, val_col3);  -- i_neighboor
       
       -- pass the values to the signals 
       w_t <= std_logic_vector(to_unsigned (val_col0, 8));
       w_z <= std_logic_vector(to_unsigned (val_col1, 3));
       w_sample <= std_logic_vector(to_unsigned (val_col2, SAMPLE_SIZE));
       w_neighboor <= std_logic_vector(to_unsigned (val_col3, SAMPLE_SIZE));
       
       w_start <= '1';
       if(test = 0) then
         wait for c_CLK_PERIOD*5.5;
         test := 1;
       else
         wait for c_CLK_PERIOD*5;
       end if;
       
     end loop;
     
     file_close(input_buff);
     wait;
   end process p_text;      
end Behavioral;
