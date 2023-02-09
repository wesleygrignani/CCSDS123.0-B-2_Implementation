-----------------------------------------------------------------------------------------------------
-- Name: Wesley Grignani
-- Laboratory of Embedded and Distributed Systems (LEDS) - UNIVALI
-----------------------------------------------------------------------------------------------------

library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
use IEEE.NUMERIC_STD.ALL;
library work;
use work.ccsds123_B2_package.all;

entity mem_init is
  port (i_clk         : in  std_logic; -- clock
        i_en          : in  std_logic; -- enable
        o_acc_value   : out std_logic_vector(ACC_SIZE-1 downto 0);    -- valor que sera inicializado em todos os reg acc
        o_count_value : out std_logic_vector(COUNT_SIZE-1 downto 0)); -- valor que sera inicializado em todos os reg acc
end mem_init;

architecture Behavioral of mem_init is
signal w_acc_value, w_count_value : integer := 0;

begin

  --process(i_clk, i_en)
  --begin
    --if(rising_edge(i_clk) and i_en = '1') then 
  w_count_value <= 2**INI_COUNT_EXP;
  w_acc_value <= (w_count_value*(3*(2**(ACCUMULATOR_INIT+6))-49))/128;
    --end if;
  --end process;
  
  o_count_value <= std_logic_vector(to_unsigned(w_count_value, COUNT_SIZE));
  o_acc_value <= std_logic_vector(to_unsigned(w_acc_value, ACC_SIZE));
  
end Behavioral;
