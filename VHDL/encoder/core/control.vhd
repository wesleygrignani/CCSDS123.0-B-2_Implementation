-----------------------------------------------------------------------------------------------------
-- Name: Wesley Grignani
-- Laboratory of Embedded and Distributed Systems (LEDS) - UNIVALI
-----------------------------------------------------------------------------------------------------

library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
use IEEE.NUMERIC_STD.ALL;
library work;
use work.ccsds123_B2_package.all;

entity control is
  port (i_clk                : in  std_logic;
        i_rst                : in  std_logic;
        i_start              : in  std_logic;
        i_uz                 : in  std_logic_vector(KZ_SIZE-1 downto 0); -- vem do datapath
        i_t                  : in  std_logic_vector(7 downto 0); -- vem do datapath
        i_z                  : in  std_logic_vector(2 downto 0); -- vem do datapath
        o_en_samples         : out std_logic;  -- habilita registrador pra guardar mapped, i_z e i_t da amostra a ser codificada
        o_en_mem_init        : out std_logic;  -- habilita inicialização das memorias
        o_sel_muxs           : out std_logic; 
        o_sel_muxs_encoded   : out std_logic_vector(1 downto 0);
        o_en_count_reg       : out std_logic_vector(4 downto 0);
        o_en_acc_reg         : out std_logic_vector(4 downto 0);
        o_en_encode_mapped   : out std_logic;  -- habilita calculo da codificacao da amostra com signal
        o_en_calc_kz_uz      : out std_logic;  -- habiita calculo de kz e uz
        o_en_encode_uzkz     : out std_logic;  -- habilita calculo da codificacao da amostra com kz e uz
        o_en_encode_umax     : out std_logic;  -- habilita calculo da codificacao da amostra com umax
        o_en_att_mem         : out std_logic;  -- habilita atualizacao das memorias
        o_valid              : out std_logic); -- indica que a saída pode ser lida
end control;

architecture Behavioral of control is

type t_STATE is (s_mem_init, s_mem_aux, s_init, s_verify_t, s_encode_mapped, s_encode_mapped_reg, s_calc_kz_uz, s_verify_uz, s_encode_uzkz, s_encode_umax, s_att_mem); -- new FSM type
signal r_STATE : t_STATE; -- state register
signal w_NEXT  : t_STATE; -- next state

begin

  -- STATE TRANSITION PROCESS
  p_STATE : process (i_rst, i_clk)
  begin
    if (i_rst = '1') then
      r_STATE <= s_init; -- estado inicial
    elsif (rising_edge(i_clk)) then
      r_STATE <= w_NEXT; -- proximo estado
    end if;
  end process;
  
  -- NEXT STATE PROCESS 
  p_NEXT : process (r_STATE, i_start, i_t, i_uz)
  begin
    case(r_STATE) is 
      
      -- estado que inicializa as memorias acumulador e contador       
      when s_mem_init => w_NEXT <= s_mem_aux;
      
      when s_mem_aux => w_NEXT <= s_init;
      
      when s_init => if(i_start = '1') then
                       w_NEXT <= s_verify_t;
                     else 
                       w_NEXT <= s_init;
                     end if;
      
      when s_verify_t => if(to_integer(unsigned(i_t)) > 0) then
                           w_NEXT <= s_calc_kz_uz;
                         else
                           w_NEXT <= s_encode_mapped;
                         end if;
      
       when s_encode_mapped => w_NEXT <= s_encode_mapped_reg;
       
       when s_encode_mapped_reg => w_NEXT <= s_init;                    
                        
       when s_calc_kz_uz => w_NEXT <= s_verify_uz;
       
       when s_verify_uz => if(to_integer(unsigned(i_uz)) < UMAX) then 
                             w_NEXT <= s_encode_uzkz;
                           else 
                             w_NEXT <= s_encode_umax;
                           end if;
                          
       when s_encode_uzkz => w_NEXT <= s_att_mem;
       
       when s_encode_umax => w_NEXT <= s_att_mem;
       
       when s_att_mem => w_NEXT <= s_init;
       
      when others => w_NEXT <= s_init;
       
    end case;
  end process;
  
  
  -- CONTROL SIGNALS
  o_en_samples <= '1' when i_start = '1' else '0';
  
  -- inicialização da memoria
  o_en_mem_init <= '1' when r_STATE = s_mem_init or r_STATE = s_mem_aux else '0';
  o_sel_muxs <= '1' when r_STATE = s_mem_init or r_STATE = s_mem_aux else '0';
  
  o_en_count_reg <= "11111" when r_STATE = s_mem_aux or r_STATE = s_mem_init else 
                    "00001" when i_z = "000" and r_STATE = s_att_mem else
                    "00010" when i_z = "001" and r_STATE = s_att_mem else
                    "00100" when i_z = "010" and r_STATE = s_att_mem else
                    "01000" when i_z = "011" and r_STATE = s_att_mem else 
                    "10000" when i_z = "100" and r_STATE = s_att_mem else "00000";
                    
  o_en_acc_reg <= "11111" when r_STATE = s_mem_aux or r_STATE = s_mem_init else 
                  "00001" when i_z = "000" and r_STATE = s_att_mem else
                  "00010" when i_z = "001" and r_STATE = s_att_mem else
                  "00100" when i_z = "010" and r_STATE = s_att_mem else
                  "01000" when i_z = "011" and r_STATE = s_att_mem else 
                  "10000" when i_z = "100" and r_STATE = s_att_mem else "00000";
    
  o_en_calc_kz_uz <= '1' when r_STATE = s_calc_kz_uz else '0';
  
  o_en_encode_mapped <= '1' when r_STATE = s_encode_mapped else '0';
  o_en_encode_uzkz <= '1' when r_STATE = s_encode_uzkz else '0';
  o_en_encode_umax <= '1' when r_STATE = s_encode_umax else '0';
  o_sel_muxs_encoded <= "00" when r_STATE = s_encode_uzkz else 
                        "01" when r_STATE = s_encode_umax else 
                        "10" when r_STATE = s_encode_mapped_reg else "00";
  
  o_en_att_mem <= '1' when r_STATE = s_att_mem else '0';
  
  o_valid <= '1' when r_STATE = s_encode_mapped_reg or r_STATE = s_encode_umax or r_STATE = s_att_mem else '0';

end Behavioral;
