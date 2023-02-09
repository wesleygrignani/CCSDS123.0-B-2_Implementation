-----------------------------------------------------------------------------------------------------
-- Name: Wesley Grignani
-- Laboratory of Embedded and Distributed Systems (LEDS) - UNIVALI
-----------------------------------------------------------------------------------------------------

library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
use IEEE.NUMERIC_STD.ALL;

entity i_t_reg is
  port (i_clk : in  std_logic;
        i_en  : in  std_logic;
        i_t   : in  std_logic_vector(7 downto 0);
        o_t   : out std_logic_vector(7 downto 0));
end i_t_reg;

architecture Behavioral of i_t_reg is
begin
  
  process(i_clk, i_en)
  begin 
    if(rising_edge(i_clk) and i_en = '1') then
      o_t <= i_t;
    end if;
  end process;
  
end Behavioral;
