-----------------------------------------------------------------------------------------------------
-- Name: Wesley Grignanii
-- Laboratory of Embedded and Distributed Systems (LEDS) - UNIVALI
-----------------------------------------------------------------------------------------------------

library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
use IEEE.NUMERIC_STD.ALL;
library work;
use work.ccsds123_B2_package.all;

entity acc_reg is
  port ( i_clk  : in  std_logic;
         i_en   : in  std_logic;
         i_acc  : in  std_logic_vector(ACC_SIZE-1 downto 0);
         o_acc  : out std_logic_vector(ACC_SIZE-1 downto 0));
end acc_reg;

architecture Behavioral of acc_reg is
begin

  process(i_clk, i_en)
  begin 
    if(rising_edge(i_clk) and i_en = '1') then
      o_acc <= i_acc;
    end if;
  end process;
  
end Behavioral;
