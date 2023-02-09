-----------------------------------------------------------------------------------------------------
-- Name: Wesley Grignani
-- Laboratory of Embedded and Distributed Systems (LEDS) - UNIVALI
-----------------------------------------------------------------------------------------------------

library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
use IEEE.NUMERIC_STD.ALL;
library work;
use work.ccsds123_B2_package.all;

entity update_acc_count is
  port ( i_clk       : in  std_logic;
         i_en        : in  std_logic;
         i_z         : in  std_logic_vector(2 downto 0);
         i_acc0      : in  std_logic_vector(ACC_SIZE-1 downto 0);
         i_acc1      : in  std_logic_vector(ACC_SIZE-1 downto 0);
         i_acc2      : in  std_logic_vector(ACC_SIZE-1 downto 0);
         i_acc3      : in  std_logic_vector(ACC_SIZE-1 downto 0);
         i_acc4      : in  std_logic_vector(ACC_SIZE-1 downto 0);
         i_count0    : in  std_logic_vector(COUNT_SIZE-1 downto 0);
         i_count1    : in  std_logic_vector(COUNT_SIZE-1 downto 0);
         i_count2    : in  std_logic_vector(COUNT_SIZE-1 downto 0);
         i_count3    : in  std_logic_vector(COUNT_SIZE-1 downto 0);
         i_count4    : in  std_logic_vector(COUNT_SIZE-1 downto 0);
         i_mapped    : in  std_logic_vector(15 downto 0);
         o_new_acc   : out std_logic_vector(ACC_SIZE-1 downto 0);
         o_new_count : out std_logic_vector(COUNT_SIZE-1 downto 0));
end update_acc_count;

architecture Behavioral of update_acc_count is
signal w_limit, w_mapped : integer := 0;
signal w_acc_aux, w_count_aux, w_out_acc, w_out_count : integer := 0; 

begin
  w_limit <= (2**RESCALING_COUNTER_SIZE) - 1; -- calculo do limite
  w_mapped <= to_integer(unsigned(i_mapped));
  process(i_z, i_acc0, i_acc1, i_acc2, i_acc3, i_acc4, i_count0, i_count1, i_count2, i_count3, i_count4)
  begin
    case(i_z) is 
    
      when "000" => w_acc_aux   <= to_integer(unsigned(i_acc0));
                    w_count_aux <= to_integer(unsigned(i_count0));
      
      when "001" => w_acc_aux   <= to_integer(unsigned(i_acc1));
                    w_count_aux <= to_integer(unsigned(i_count1));
                    
      when "010" => w_acc_aux   <= to_integer(unsigned(i_acc2));
                    w_count_aux <= to_integer(unsigned(i_count2));
                    
      when "011" => w_acc_aux   <= to_integer(unsigned(i_acc3));
                    w_count_aux <= to_integer(unsigned(i_count3));
      
      when "100" => w_acc_aux   <= to_integer(unsigned(i_acc4));
                    w_count_aux <= to_integer(unsigned(i_count4));
                    
      when others => w_acc_aux   <= 0;            
                     w_count_aux <= 0;
    end case;             
  end process;
  
  
  process(i_clk, i_en)
  begin 
    if(rising_edge(i_clk) and i_en = '1') then
      if(w_count_aux < w_limit) then
        w_out_acc <= w_acc_aux + w_mapped;
        w_out_count <= w_count_aux + 1;
      else
        w_out_acc <= (w_acc_aux + w_mapped + 1)/2;
        w_out_count <= (w_count_aux + 1)/2;
      end if;
    end if;
  end process;
  
  o_new_acc <= std_logic_vector(to_unsigned(w_out_acc, ACC_SIZE));
  o_new_count <= std_logic_vector(to_unsigned(w_out_count, COUNT_SIZE));
  
end Behavioral;
