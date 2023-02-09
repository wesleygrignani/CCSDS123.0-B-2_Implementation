-----------------------------------------------------------------------------------------------------
-- Name: Wesley Grignani
-- Laboratory of Embedded and Distributed Systems (LEDS) - UNIVALI
-----------------------------------------------------------------------------------------------------

library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
use IEEE.NUMERIC_STD.ALL;

entity tb_encoder is
--  Port ( );
end tb_encoder;

architecture Behavioral of tb_encoder is

component top is
  port ( i_clk              : in  std_logic;
         i_rst              : in  std_logic;
         i_start            : in  std_logic;
         i_t                : in  std_logic_vector(7 downto 0); 
         i_z                : in  std_logic_vector(2 downto 0); 
         i_mapped           : in  std_logic_vector(15 downto 0);
         o_encoded          : out std_logic_vector(31 downto 0); 
         o_out_bits_written : out std_logic_vector(5 downto 0);
         o_valid            : out std_logic);
end component;

signal w_clk, w_rst, w_start, w_valid : std_logic := '0';
signal w_t : std_logic_vector(7 downto 0) := (others => '0');
signal w_z : std_logic_vector(2 downto 0) := (others => '0');
signal w_mapped : std_logic_vector(15 downto 0) := (others => '0');
signal w_encoded : std_logic_vector(31 downto 0) := (others => '0');
signal w_written_bits : std_logic_vector(5 downto 0) := (others => '0');

constant c_CLK_PERIOD : time := 10 ns;

begin
  
  p_CLK : process 
  begin
    w_clk <= '0';
    wait for c_CLK_PERIOD/2;
    w_clk <= '1';
    wait for c_CLK_PERIOD/2;
  end process p_CLK;
  
  p_TOP : top
    port map (i_clk              => w_clk,
              i_rst              => w_rst,
              i_start            => w_start,
              i_t                => w_t,
              i_z                => w_z,
              i_mapped           => w_mapped,
              o_encoded          => w_encoded,
              o_out_bits_written => w_written_bits,
              o_valid            => w_valid);
              
              
   p_INPUTS : process
   begin
     w_rst <= '0';
     w_start <= '0';
     w_t <= "00000000";
     w_z <= "000";
     w_mapped <= std_logic_vector(to_unsigned(61273, 16));
     wait for c_CLK_PERIOD*2;
     
     w_start <= '1';
     wait for c_CLK_PERIOD*1;
     w_start <= '0';
     wait for c_CLK_PERIOD*3;
     
     w_t <= "00000000";
     w_z <= "001";
     w_mapped <= std_logic_vector(to_unsigned(140, 16));
     wait for c_CLK_PERIOD;
     w_start <= '1';
     wait for c_CLK_PERIOD*1;
     w_start <= '0';
     wait for c_CLK_PERIOD*3;
     
     w_t <= "00000000";
     w_z <= "010";
     w_mapped <= std_logic_vector(to_unsigned(318, 16));
     wait for c_CLK_PERIOD;
     w_start <= '1';
     wait for c_CLK_PERIOD*1;
     w_start <= '0';
     wait for c_CLK_PERIOD*3;
     
     w_t <= "00000001";
     w_z <= "000";
     w_mapped <= std_logic_vector(to_unsigned(10, 16));
     wait for c_CLK_PERIOD;
     w_start <= '1';
     wait for c_CLK_PERIOD*1;
     w_start <= '0';
     wait for c_CLK_PERIOD*7;
     
     w_t <= "00000010";
     w_z <= "001";
     w_mapped <= std_logic_vector(to_unsigned(54, 16));
     wait for c_CLK_PERIOD;
     w_start <= '1';
     wait for c_CLK_PERIOD*1;
     w_start <= '0';
     wait for c_CLK_PERIOD*7;
     
     w_t <= "00000011";
     w_z <= "010";
     w_mapped <= std_logic_vector(to_unsigned(4, 16));
     wait for c_CLK_PERIOD;
     w_start <= '1';
     wait for c_CLK_PERIOD*1;
     w_start <= '0';
     wait for c_CLK_PERIOD*7;
     
     w_t <= "00000100";
     w_z <= "011";
     w_mapped <= std_logic_vector(to_unsigned(42, 16));
     wait for c_CLK_PERIOD;
     w_start <= '1';
     wait for c_CLK_PERIOD*1;
     w_start <= '0';
     wait for c_CLK_PERIOD*7;
     
     w_t <= "00000101";
     w_z <= "100";
     w_mapped <= std_logic_vector(to_unsigned(57, 16));
     wait for c_CLK_PERIOD;
     w_start <= '1';
     wait for c_CLK_PERIOD*1;
     w_start <= '0';
     wait for c_CLK_PERIOD*7;
     
     w_t <= "00000110";
     w_z <= "000";
     w_mapped <= std_logic_vector(to_unsigned(49, 16));
     wait for c_CLK_PERIOD;
     w_start <= '1';
     wait for c_CLK_PERIOD*1;
     w_start <= '0';
     wait for c_CLK_PERIOD*7;
     
     assert false report "Test done." severity note;
     wait;
   end process p_INPUTS;

end Behavioral;
