-----------------------------------------------------------------------------------------------------
-- Name: Wesley Grignani
-- Laboratory of Embedded and Distributed Systems (LEDS) - UNIVALI
-----------------------------------------------------------------------------------------------------
library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
use IEEE.NUMERIC_STD.ALL;
library work;
use work.ccsds123_B2_package.all;

entity mux_acc is
  port ( i_acc_from_init   : in  std_logic_vector(ACC_SIZE-1 downto 0);
         i_acc_from_update : in  std_logic_vector(ACC_SIZE-1 downto 0);
         i_sel             : in  std_logic;
         o_acc_out_mux     : out std_logic_vector(ACC_SIZE-1 downto 0));
end mux_acc;

architecture Behavioral of mux_acc is
begin
  
  p_mux : process(i_acc_from_update, i_acc_from_init, i_sel)
  begin 
    case i_sel is 
      when '1'    => o_acc_out_mux    <= i_acc_from_init;
      when '0'    => o_acc_out_mux    <= i_acc_from_update;
      when others => o_acc_out_mux    <= (others => '0');
    end case;
  end process p_mux;
  
end Behavioral;
