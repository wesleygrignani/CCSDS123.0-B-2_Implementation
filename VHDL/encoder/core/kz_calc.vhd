-----------------------------------------------------------------------------------------------------
-- Name: Wesley Grignani
-- Laboratory of Embedded and Distributed Systems (LEDS) - UNIVALI
-----------------------------------------------------------------------------------------------------

library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
use IEEE.NUMERIC_STD.ALL;
use IEEE.math_real.ALL;
library work;
use work.ccsds123_B2_package.all;

entity kz_calc is
  port ( i_clk       : in  std_logic;
         i_en        : in  std_logic;
         i_acc_reg   : in  std_logic_vector(ACC_SIZE-1 downto 0);
         i_count_reg : in  std_logic_vector(COUNT_SIZE-1 downto 0);
         i_mapped    : in  std_logic_vector(15 downto 0);
         o_kz        : out std_logic_vector(KZ_SIZE-1 downto 0);
         o_uz        : out std_logic_vector(KZ_SIZE-1 downto 0)); 
end kz_calc;

architecture Behavioral of kz_calc is
signal w_acc_reg, w_count_reg, w_kz : integer := 0;
--signal w_aux : real := 0.0;
signal w_teste : integer := 0;
signal w_mapped, w_uz : unsigned(15 downto 0);
        
begin
  w_acc_reg <= to_integer(unsigned(i_acc_reg));
  w_count_reg <= to_integer(unsigned(i_count_reg));
  w_mapped <= unsigned(i_mapped);
  
  process(i_clk, i_en) 
  begin
    if(rising_edge(i_clk) and i_en = '1') then
      --w_aux <= real((w_acc_reg + ((49*w_count_reg) / 128)) / w_count_reg);
        w_teste <= (w_acc_reg + ((49*w_count_reg) / 128) / w_count_reg);
    end if;
  end process;
  
  w_teste <= integer(w_teste) when w_teste > 0 else 0;
  
  o_kz <= std_logic_vector(to_unsigned(14, KZ_SIZE)) when w_teste > 14 else 
          std_logic_vector(to_unsigned(0, KZ_SIZE)) when w_teste < 0 else
          std_logic_vector(to_unsigned(w_teste, KZ_SIZE));
  
  w_uz <= shift_right(w_mapped, w_teste);
  o_uz <= std_logic_vector(w_uz);
  
end Behavioral;
