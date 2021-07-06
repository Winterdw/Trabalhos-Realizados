/* The following code was generated by JFlex 1.4.3 on 26/10/19 21:19 */

package codigo;
import static codigo.Tokens.*; // SERÁ CRIADA A CLASSE Tokens DO TIPO Enum PARA SER IMPORTADA.


/**
 * This class is a scanner generated by 
 * <a href="http://www.jflex.de/">JFlex</a> 1.4.3
 * on 26/10/19 21:19 from the specification file
 * <tt>C:/Users/Windows/Desktop/Engenharia da Computação/8° Período/Compiladores/Trabalho Final/analisador_lexico/src/codigo/Lexer.flex</tt>
 */
class Lexer {

  /** This character denotes the end of file */
  public static final int YYEOF = -1;

  /** initial size of the lookahead buffer */
  private static final int ZZ_BUFFERSIZE = 16384;

  /** lexical states */
  public static final int YYINITIAL = 0;

  /**
   * ZZ_LEXSTATE[l] is the state in the DFA for the lexical state l
   * ZZ_LEXSTATE[l+1] is the state in the DFA for the lexical state l
   *                  at the beginning of a line
   * l is of the form l = 2*k, k a non negative integer
   */
  private static final int ZZ_LEXSTATE[] = { 
     0, 0
  };

  /** 
   * Translates characters to character classes
   */
  private static final String ZZ_CMAP_PACKED = 
    "\11\0\1\0\1\4\2\0\1\0\22\0\1\45\1\46\1\0\2\0"+
    "\1\0\1\0\1\0\1\6\1\5\1\15\1\0\1\3\1\50\1\0"+
    "\1\47\12\2\1\0\1\26\1\0\1\0\1\0\1\0\1\0\1\1"+
    "\1\1\1\1\1\13\1\1\1\1\2\1\1\1\2\1\1\10\3\1"+
    "\1\1\2\1\1\14\2\1\1\1\1\1\3\1\1\37\1\0\1\40"+
    "\1\0\1\1\1\0\1\24\1\20\1\23\1\35\1\27\1\42\1\41"+
    "\1\43\1\22\2\1\1\21\1\36\1\33\1\31\1\16\1\1\1\30"+
    "\1\25\1\32\1\17\1\34\1\44\3\1\1\7\1\12\1\11\52\0"+
    "\1\0\uff57\0";

  /** 
   * Translates characters to character classes
   */
  private static final char [] ZZ_CMAP = zzUnpackCMap(ZZ_CMAP_PACKED);

  /** 
   * Translates DFA states to action switch labels.
   */
  private static final int [] ZZ_ACTION = zzUnpackAction();

  private static final String ZZ_ACTION_PACKED_0 =
    "\1\0\2\1\1\2\1\3\15\1\1\4\1\0\5\4"+
    "\1\5\7\4\1\6\1\0\4\4\1\7\7\4\1\2"+
    "\4\4\1\0\4\4\1\5\1\4\1\10\2\4\1\11"+
    "\1\4\1\0\1\12\2\4\2\0\1\4\7\0\1\13"+
    "\1\0\2\4\1\0\1\4\5\0\1\13\1\0\1\4"+
    "\6\0\5\4\4\0\5\4\4\0\5\4\1\0\1\14"+
    "\1\0\2\4\1\0\2\4\1\0\1\4\6\0";

  private static int [] zzUnpackAction() {
    int [] result = new int[137];
    int offset = 0;
    offset = zzUnpackAction(ZZ_ACTION_PACKED_0, offset, result);
    return result;
  }

  private static int zzUnpackAction(String packed, int offset, int [] result) {
    int i = 0;       /* index in packed string  */
    int j = offset;  /* index in unpacked array */
    int l = packed.length();
    while (i < l) {
      int count = packed.charAt(i++);
      int value = packed.charAt(i++);
      do result[j++] = value; while (--count > 0);
    }
    return j;
  }


  /** 
   * Translates a state to a row index in the transition table
   */
  private static final int [] ZZ_ROWMAP = zzUnpackRowMap();

  private static final String ZZ_ROWMAP_PACKED_0 =
    "\0\0\0\51\0\122\0\173\0\244\0\315\0\366\0\u011f"+
    "\0\u0148\0\u0171\0\u019a\0\u01c3\0\u01ec\0\u0215\0\u023e\0\u0267"+
    "\0\u0290\0\u02b9\0\122\0\u02e2\0\u030b\0\u0334\0\u035d\0\u0386"+
    "\0\u03af\0\122\0\u03d8\0\u0401\0\u042a\0\u0453\0\u047c\0\u04a5"+
    "\0\u04ce\0\u04f7\0\u0520\0\u0549\0\u0572\0\u059b\0\u05c4\0\u05ed"+
    "\0\u0616\0\u063f\0\u0668\0\u0691\0\u06ba\0\u06e3\0\u070c\0\51"+
    "\0\u0735\0\u075e\0\u0787\0\u07b0\0\u07d9\0\u0802\0\u082b\0\u0854"+
    "\0\u087d\0\u08a6\0\u08cf\0\u08f8\0\u0921\0\u094a\0\u0973\0\u099c"+
    "\0\u09c5\0\51\0\u09ee\0\u0a17\0\u0a40\0\u0a69\0\u0a92\0\u0abb"+
    "\0\u0ae4\0\u0b0d\0\u0b36\0\u0b5f\0\u0b88\0\u0bb1\0\51\0\u0bda"+
    "\0\u0c03\0\u0c2c\0\u0c55\0\u0c7e\0\u0ca7\0\u0cd0\0\u0cf9\0\u0d22"+
    "\0\u0d4b\0\u0bda\0\u0d74\0\u0d9d\0\u0dc6\0\u0def\0\u0e18\0\u0e41"+
    "\0\u0e6a\0\u0e93\0\u0ebc\0\u0ee5\0\u0f0e\0\u0f37\0\u0f60\0\u0f89"+
    "\0\u0fb2\0\u0fdb\0\u1004\0\u102d\0\u1056\0\u107f\0\u10a8\0\u10d1"+
    "\0\u10fa\0\u1123\0\u114c\0\u1175\0\u119e\0\u11c7\0\u11f0\0\u1219"+
    "\0\u1242\0\u126b\0\u1294\0\u12bd\0\u12e6\0\u130f\0\u1338\0\u1361"+
    "\0\u138a\0\u13b3\0\u13dc\0\u1405\0\u142e\0\u1457\0\u1480\0\u14a9"+
    "\0\u14d2";

  private static int [] zzUnpackRowMap() {
    int [] result = new int[137];
    int offset = 0;
    offset = zzUnpackRowMap(ZZ_ROWMAP_PACKED_0, offset, result);
    return result;
  }

  private static int zzUnpackRowMap(String packed, int offset, int [] result) {
    int i = 0;  /* index in packed string  */
    int j = offset;  /* index in unpacked array */
    int l = packed.length();
    while (i < l) {
      int high = packed.charAt(i++) << 16;
      result[j++] = high | packed.charAt(i++);
    }
    return j;
  }

  /** 
   * The transition table of the DFA
   */
  private static final int [] ZZ_TRANS = zzUnpackTrans();

  private static final String ZZ_TRANS_PACKED_0 =
    "\1\2\1\3\1\4\1\2\1\5\1\2\1\6\1\2"+
    "\1\3\2\2\1\3\1\7\1\2\1\10\1\3\1\11"+
    "\1\3\1\12\1\13\2\3\1\2\1\14\1\15\3\3"+
    "\1\16\1\3\1\17\2\2\1\3\1\20\1\3\1\21"+
    "\2\2\1\22\1\2\52\0\2\23\5\0\1\23\2\0"+
    "\2\23\1\0\10\23\1\0\10\23\2\0\4\23\6\0"+
    "\1\4\52\0\1\5\114\0\1\24\1\0\2\23\5\0"+
    "\1\23\2\0\2\23\1\0\10\23\1\0\3\23\1\25"+
    "\4\23\2\0\4\23\5\0\2\23\5\0\1\23\2\0"+
    "\2\23\1\0\1\23\1\26\6\23\1\0\1\23\1\27"+
    "\6\23\2\0\4\23\5\0\2\23\5\0\1\23\2\0"+
    "\2\23\1\0\10\23\1\0\2\23\1\30\5\23\2\0"+
    "\4\23\5\0\2\23\5\0\1\23\2\0\2\23\1\0"+
    "\10\23\1\0\4\23\1\31\3\23\2\0\1\23\1\32"+
    "\2\23\5\0\2\23\5\0\1\23\2\0\2\23\1\0"+
    "\3\23\1\33\4\23\1\0\10\23\2\0\4\23\5\0"+
    "\2\23\5\0\1\23\2\0\2\23\1\0\3\23\1\34"+
    "\4\23\1\0\10\23\2\0\4\23\5\0\2\23\5\0"+
    "\1\23\2\0\2\23\1\0\10\23\1\0\1\35\7\23"+
    "\2\0\4\23\5\0\2\23\5\0\1\23\2\0\2\23"+
    "\1\0\10\23\1\0\2\23\1\36\5\23\2\0\4\23"+
    "\5\0\2\23\5\0\1\23\2\0\2\23\1\0\6\23"+
    "\1\37\1\23\1\0\10\23\2\0\4\23\5\0\2\23"+
    "\5\0\1\23\2\0\2\23\1\0\3\23\1\40\4\23"+
    "\1\0\10\23\2\0\4\23\5\0\2\23\5\0\1\23"+
    "\2\0\2\23\1\0\10\23\1\0\10\23\2\0\2\23"+
    "\1\41\1\23\53\0\1\42\3\0\1\43\47\0\2\23"+
    "\5\0\1\23\2\0\2\23\1\0\10\23\1\0\1\23"+
    "\1\44\6\23\2\0\4\23\5\0\2\23\5\0\1\23"+
    "\2\0\2\23\1\0\2\23\1\45\5\23\1\0\10\23"+
    "\2\0\4\23\5\0\2\23\5\0\1\23\2\0\2\23"+
    "\1\0\4\23\1\46\3\23\1\0\10\23\2\0\4\23"+
    "\5\0\2\23\5\0\1\23\2\0\2\23\1\0\10\23"+
    "\1\0\2\23\1\47\5\23\2\0\4\23\5\0\2\23"+
    "\5\0\1\23\2\0\2\23\1\0\10\23\1\0\3\23"+
    "\1\50\4\23\2\0\4\23\5\0\2\23\5\0\1\23"+
    "\2\0\2\23\1\0\6\23\1\51\1\23\1\0\10\23"+
    "\2\0\4\23\5\0\2\23\5\0\1\23\2\0\2\23"+
    "\1\0\7\23\1\52\1\0\10\23\2\0\4\23\5\0"+
    "\2\23\5\0\1\23\2\0\2\23\1\0\10\23\1\0"+
    "\3\23\1\53\4\23\2\0\4\23\5\0\2\23\5\0"+
    "\1\23\2\0\2\23\1\0\4\23\1\54\3\23\1\0"+
    "\10\23\2\0\4\23\5\0\2\23\5\0\1\23\2\0"+
    "\2\23\1\0\4\23\1\55\3\23\1\0\10\23\2\0"+
    "\4\23\5\0\2\23\5\0\1\23\2\0\2\23\1\0"+
    "\10\23\1\0\2\23\1\56\5\23\2\0\4\23\5\0"+
    "\2\23\5\0\1\23\2\0\2\23\1\0\4\23\1\57"+
    "\3\23\1\0\10\23\2\0\4\23\4\0\4\42\1\0"+
    "\44\42\2\0\1\43\2\0\1\60\44\0\2\23\5\0"+
    "\1\23\2\0\2\23\1\0\4\23\1\61\3\23\1\0"+
    "\10\23\2\0\4\23\5\0\2\23\5\0\1\23\2\0"+
    "\2\23\1\0\3\23\1\62\4\23\1\0\10\23\2\0"+
    "\4\23\5\0\2\23\5\0\1\23\2\0\2\23\1\0"+
    "\10\23\1\0\4\23\1\63\3\23\2\0\4\23\5\0"+
    "\2\23\5\0\1\23\2\0\2\23\1\0\3\23\1\64"+
    "\4\23\1\0\10\23\2\0\4\23\5\0\2\23\5\0"+
    "\1\23\2\0\2\23\1\0\10\23\1\0\10\23\1\65"+
    "\1\0\4\23\5\0\2\23\5\0\1\23\2\0\2\23"+
    "\1\0\7\23\1\66\1\0\10\23\2\0\4\23\5\0"+
    "\2\23\5\0\1\23\2\0\2\23\1\0\10\23\1\0"+
    "\1\32\7\23\2\0\4\23\5\0\2\23\5\0\1\23"+
    "\2\0\2\23\1\0\1\23\1\67\6\23\1\0\10\23"+
    "\2\0\4\23\5\0\2\23\5\0\1\23\2\0\2\23"+
    "\1\0\10\23\1\0\6\23\1\50\1\23\2\0\4\23"+
    "\5\0\2\23\5\0\1\23\2\0\2\23\1\0\10\23"+
    "\1\0\4\23\1\32\3\23\2\0\4\23\5\0\2\23"+
    "\5\0\1\23\2\0\2\23\1\0\6\23\1\31\1\23"+
    "\1\0\10\23\2\0\4\23\5\0\2\23\5\0\1\23"+
    "\2\0\2\23\1\0\3\23\1\52\4\23\1\0\10\23"+
    "\2\0\4\23\5\0\2\23\5\0\1\23\2\0\2\23"+
    "\1\0\10\23\1\0\4\23\1\70\3\23\2\0\4\23"+
    "\5\0\2\23\5\0\1\23\2\0\2\23\1\0\4\23"+
    "\1\71\3\23\1\0\10\23\2\0\4\23\5\0\2\23"+
    "\5\0\1\23\2\0\2\23\1\0\10\23\1\0\3\23"+
    "\1\72\4\23\2\0\4\23\5\0\2\23\5\0\1\23"+
    "\2\0\2\23\1\0\10\23\1\0\1\73\7\23\2\0"+
    "\4\23\44\0\1\74\11\0\2\23\5\0\1\23\2\0"+
    "\2\23\1\0\7\23\1\32\1\0\10\23\2\0\4\23"+
    "\5\0\2\23\5\0\1\23\2\0\2\23\1\0\10\23"+
    "\1\0\1\23\1\75\6\23\2\0\4\23\5\0\2\23"+
    "\5\0\1\23\2\0\2\23\1\0\10\23\1\0\10\23"+
    "\2\0\1\50\3\23\5\0\2\23\5\0\1\23\2\0"+
    "\2\23\1\0\5\23\1\32\2\23\1\0\10\23\2\0"+
    "\4\23\5\0\2\23\5\0\1\23\2\0\2\23\1\0"+
    "\3\23\1\55\4\23\1\0\10\23\2\0\4\23\5\0"+
    "\2\23\5\0\1\23\2\0\2\23\1\0\6\23\1\76"+
    "\1\23\1\0\10\23\2\0\4\23\5\0\1\77\6\0"+
    "\1\77\2\0\2\77\1\0\10\77\1\0\10\77\2\0"+
    "\4\77\5\0\2\23\5\0\1\23\2\0\2\23\1\0"+
    "\10\23\1\0\4\23\1\100\3\23\2\0\4\23\5\0"+
    "\2\23\5\0\1\23\2\0\2\23\1\0\10\23\1\0"+
    "\4\23\1\50\3\23\2\0\4\23\5\0\2\77\1\101"+
    "\4\0\1\77\2\0\2\77\1\0\10\77\1\102\10\77"+
    "\2\0\4\77\5\0\1\103\1\104\1\105\1\0\1\106"+
    "\2\0\1\103\2\0\2\103\1\0\10\103\1\0\4\103"+
    "\1\107\3\103\2\0\4\103\1\0\1\105\16\0\1\110"+
    "\3\0\1\111\1\0\1\112\11\0\1\113\5\0\1\114"+
    "\7\0\2\103\2\0\1\115\1\116\1\0\1\103\2\0"+
    "\2\103\1\0\10\103\1\117\10\103\2\0\4\103\4\0"+
    "\1\120\1\121\1\122\1\120\1\0\3\120\1\121\2\120"+
    "\2\121\1\120\10\121\1\120\10\121\2\120\4\121\4\120"+
    "\2\0\1\120\54\0\1\123\43\0\2\103\2\0\1\115"+
    "\1\116\1\0\1\103\2\0\2\103\1\0\10\103\1\117"+
    "\1\124\7\103\2\0\4\103\36\0\1\125\47\0\1\126"+
    "\52\0\1\127\46\0\1\130\40\0\1\131\55\0\1\117"+
    "\27\0\1\105\20\0\1\117\24\0\1\120\23\0\1\117"+
    "\23\0\1\23\1\121\5\0\1\23\2\0\2\23\1\0"+
    "\10\23\1\117\10\23\2\0\4\23\4\0\1\120\1\121"+
    "\1\122\1\120\1\0\3\120\1\121\2\120\2\121\1\120"+
    "\10\121\1\132\10\121\2\120\4\121\4\120\7\0\1\133"+
    "\42\0\2\103\2\0\1\115\1\116\1\0\1\103\2\0"+
    "\2\103\1\0\10\103\1\117\10\103\2\0\3\103\1\134"+
    "\34\0\1\135\51\0\1\136\51\0\1\137\40\0\1\140"+
    "\57\0\1\141\27\0\1\142\41\0\2\103\2\0\1\115"+
    "\1\116\1\0\1\103\2\0\1\103\1\143\1\0\2\103"+
    "\1\144\1\103\1\145\3\103\1\117\5\103\1\146\2\103"+
    "\2\0\1\103\1\147\2\103\26\0\1\150\47\0\1\151"+
    "\66\0\1\152\46\0\1\137\37\0\1\127\35\0\1\153"+
    "\40\0\2\103\2\0\1\115\1\116\1\0\1\103\2\0"+
    "\2\103\1\0\10\103\1\117\3\103\1\154\4\103\2\0"+
    "\4\103\5\0\2\103\2\0\1\115\1\116\1\0\1\103"+
    "\2\0\2\103\1\0\10\103\1\117\2\103\1\155\5\103"+
    "\2\0\4\103\5\0\2\103\2\0\1\115\1\116\1\0"+
    "\1\103\2\0\2\103\1\0\10\103\1\117\4\103\1\156"+
    "\3\103\2\0\4\103\5\0\2\103\2\0\1\115\1\116"+
    "\1\0\1\103\2\0\2\103\1\0\10\103\1\117\2\103"+
    "\1\157\5\103\2\0\4\103\5\0\2\103\2\0\1\115"+
    "\1\116\1\0\1\103\2\0\2\103\1\0\3\103\1\160"+
    "\4\103\1\117\10\103\2\0\4\103\37\0\1\161\44\0"+
    "\1\162\61\0\1\163\22\0\1\164\37\0\2\103\2\0"+
    "\1\115\1\116\1\0\1\103\2\0\2\103\1\0\10\103"+
    "\1\117\1\103\1\165\6\103\2\0\4\103\5\0\2\103"+
    "\2\0\1\115\1\116\1\0\1\103\2\0\2\103\1\0"+
    "\10\103\1\117\2\103\1\166\5\103\2\0\4\103\5\0"+
    "\2\103\2\0\1\115\1\116\1\0\1\103\2\0\2\103"+
    "\1\0\10\103\1\117\3\103\1\167\4\103\2\0\4\103"+
    "\5\0\2\103\2\0\1\115\1\116\1\0\1\103\2\0"+
    "\2\103\1\0\4\103\1\170\3\103\1\117\10\103\2\0"+
    "\4\103\5\0\2\103\2\0\1\115\1\116\1\0\1\103"+
    "\2\0\2\103\1\0\10\103\1\117\2\103\1\171\5\103"+
    "\2\0\4\103\45\0\1\137\33\0\1\172\25\0\1\173"+
    "\6\0\1\173\2\0\2\173\1\0\10\173\1\0\10\173"+
    "\2\0\4\173\13\0\1\174\42\0\2\103\2\0\1\115"+
    "\1\116\1\0\1\103\2\0\2\103\1\0\4\103\1\175"+
    "\3\103\1\117\10\103\2\0\4\103\5\0\2\103\2\0"+
    "\1\115\1\116\1\0\1\103\2\0\2\103\1\0\3\103"+
    "\1\176\4\103\1\117\10\103\2\0\4\103\5\0\2\103"+
    "\2\0\1\115\1\116\1\0\1\103\2\0\2\103\1\0"+
    "\10\103\1\117\10\103\2\0\4\103\1\115\4\0\2\103"+
    "\2\0\1\115\1\116\1\0\1\103\2\0\2\103\1\0"+
    "\10\103\1\117\6\103\1\167\1\103\2\0\4\103\5\0"+
    "\2\103\2\0\1\115\1\116\1\0\1\103\2\0\2\103"+
    "\1\0\6\103\1\156\1\103\1\117\10\103\2\0\4\103"+
    "\37\0\1\137\16\0\2\173\1\101\4\0\1\173\2\0"+
    "\2\173\1\0\10\173\1\0\10\173\2\0\4\173\17\0"+
    "\1\177\36\0\2\103\2\0\1\115\1\116\1\0\1\103"+
    "\2\0\2\103\1\0\10\103\1\117\4\103\1\200\3\103"+
    "\2\0\4\103\5\0\2\103\2\0\1\115\1\116\1\0"+
    "\1\103\2\0\2\103\1\0\10\103\1\117\1\201\7\103"+
    "\2\0\4\103\15\0\1\202\40\0\2\103\2\0\1\115"+
    "\1\116\1\0\1\103\2\0\2\103\1\0\10\103\1\117"+
    "\10\103\2\0\1\167\3\103\5\0\2\103\2\0\1\115"+
    "\1\116\1\0\1\103\2\0\2\103\1\0\6\103\1\203"+
    "\1\103\1\117\10\103\2\0\4\103\16\0\1\204\37\0"+
    "\2\103\2\0\1\115\1\116\1\0\1\103\2\0\2\103"+
    "\1\0\10\103\1\117\4\103\1\167\3\103\2\0\4\103"+
    "\13\0\1\205\55\0\1\206\45\0\1\207\44\0\1\210"+
    "\60\0\1\211\41\0\1\115\42\0";

  private static int [] zzUnpackTrans() {
    int [] result = new int[5371];
    int offset = 0;
    offset = zzUnpackTrans(ZZ_TRANS_PACKED_0, offset, result);
    return result;
  }

  private static int zzUnpackTrans(String packed, int offset, int [] result) {
    int i = 0;       /* index in packed string  */
    int j = offset;  /* index in unpacked array */
    int l = packed.length();
    while (i < l) {
      int count = packed.charAt(i++);
      int value = packed.charAt(i++);
      value--;
      do result[j++] = value; while (--count > 0);
    }
    return j;
  }


  /* error codes */
  private static final int ZZ_UNKNOWN_ERROR = 0;
  private static final int ZZ_NO_MATCH = 1;
  private static final int ZZ_PUSHBACK_2BIG = 2;

  /* error messages for the codes above */
  private static final String ZZ_ERROR_MSG[] = {
    "Unkown internal scanner error",
    "Error: could not match input",
    "Error: pushback value was too large"
  };

  /**
   * ZZ_ATTRIBUTE[aState] contains the attributes of state <code>aState</code>
   */
  private static final int [] ZZ_ATTRIBUTE = zzUnpackAttribute();

  private static final String ZZ_ATTRIBUTE_PACKED_0 =
    "\1\0\1\11\21\1\1\0\16\1\1\0\14\1\1\11"+
    "\4\1\1\0\13\1\1\0\1\11\2\1\2\0\1\1"+
    "\7\0\1\11\1\0\2\1\1\0\1\1\5\0\1\1"+
    "\1\0\1\1\6\0\5\1\4\0\5\1\4\0\5\1"+
    "\1\0\1\1\1\0\2\1\1\0\2\1\1\0\1\1"+
    "\6\0";

  private static int [] zzUnpackAttribute() {
    int [] result = new int[137];
    int offset = 0;
    offset = zzUnpackAttribute(ZZ_ATTRIBUTE_PACKED_0, offset, result);
    return result;
  }

  private static int zzUnpackAttribute(String packed, int offset, int [] result) {
    int i = 0;       /* index in packed string  */
    int j = offset;  /* index in unpacked array */
    int l = packed.length();
    while (i < l) {
      int count = packed.charAt(i++);
      int value = packed.charAt(i++);
      do result[j++] = value; while (--count > 0);
    }
    return j;
  }

  /** the input device */
  private java.io.Reader zzReader;

  /** the current state of the DFA */
  private int zzState;

  /** the current lexical state */
  private int zzLexicalState = YYINITIAL;

  /** this buffer contains the current text to be matched and is
      the source of the yytext() string */
  private char zzBuffer[] = new char[ZZ_BUFFERSIZE];

  /** the textposition at the last accepting state */
  private int zzMarkedPos;

  /** the current text position in the buffer */
  private int zzCurrentPos;

  /** startRead marks the beginning of the yytext() string in the buffer */
  private int zzStartRead;

  /** endRead marks the last character in the buffer, that has been read
      from input */
  private int zzEndRead;

  /** number of newlines encountered up to the start of the matched text */
  private int yyline;

  /** the number of characters up to the start of the matched text */
  private int yychar;

  /**
   * the number of characters from the last newline up to the start of the 
   * matched text
   */
  private int yycolumn;

  /** 
   * zzAtBOL == true <=> the scanner is currently at the beginning of a line
   */
  private boolean zzAtBOL = true;

  /** zzAtEOF == true <=> the scanner is at the EOF */
  private boolean zzAtEOF;

  /** denotes if the user-EOF-code has already been executed */
  private boolean zzEOFDone;

  /* user code: */
    public String lexeme;


  /**
   * Creates a new scanner
   * There is also a java.io.InputStream version of this constructor.
   *
   * @param   in  the java.io.Reader to read input from.
   */
  Lexer(java.io.Reader in) {
    this.zzReader = in;
  }

  /**
   * Creates a new scanner.
   * There is also java.io.Reader version of this constructor.
   *
   * @param   in  the java.io.Inputstream to read input from.
   */
  Lexer(java.io.InputStream in) {
    this(new java.io.InputStreamReader(in));
  }

  /** 
   * Unpacks the compressed character translation table.
   *
   * @param packed   the packed character translation table
   * @return         the unpacked character translation table
   */
  private static char [] zzUnpackCMap(String packed) {
    char [] map = new char[0x10000];
    int i = 0;  /* index in packed string  */
    int j = 0;  /* index in unpacked array */
    while (i < 164) {
      int  count = packed.charAt(i++);
      char value = packed.charAt(i++);
      do map[j++] = value; while (--count > 0);
    }
    return map;
  }


  /**
   * Refills the input buffer.
   *
   * @return      <code>false</code>, iff there was new input.
   * 
   * @exception   java.io.IOException  if any I/O-Error occurs
   */
  private boolean zzRefill() throws java.io.IOException {

    /* first: make room (if you can) */
    if (zzStartRead > 0) {
      System.arraycopy(zzBuffer, zzStartRead,
                       zzBuffer, 0,
                       zzEndRead-zzStartRead);

      /* translate stored positions */
      zzEndRead-= zzStartRead;
      zzCurrentPos-= zzStartRead;
      zzMarkedPos-= zzStartRead;
      zzStartRead = 0;
    }

    /* is the buffer big enough? */
    if (zzCurrentPos >= zzBuffer.length) {
      /* if not: blow it up */
      char newBuffer[] = new char[zzCurrentPos*2];
      System.arraycopy(zzBuffer, 0, newBuffer, 0, zzBuffer.length);
      zzBuffer = newBuffer;
    }

    /* finally: fill the buffer with new input */
    int numRead = zzReader.read(zzBuffer, zzEndRead,
                                            zzBuffer.length-zzEndRead);

    if (numRead > 0) {
      zzEndRead+= numRead;
      return false;
    }
    // unlikely but not impossible: read 0 characters, but not at end of stream    
    if (numRead == 0) {
      int c = zzReader.read();
      if (c == -1) {
        return true;
      } else {
        zzBuffer[zzEndRead++] = (char) c;
        return false;
      }     
    }

	// numRead < 0
    return true;
  }

    
  /**
   * Closes the input stream.
   */
  public final void yyclose() throws java.io.IOException {
    zzAtEOF = true;            /* indicate end of file */
    zzEndRead = zzStartRead;  /* invalidate buffer    */

    if (zzReader != null)
      zzReader.close();
  }


  /**
   * Resets the scanner to read from a new input stream.
   * Does not close the old reader.
   *
   * All internal variables are reset, the old input stream 
   * <b>cannot</b> be reused (internal buffer is discarded and lost).
   * Lexical state is set to <tt>ZZ_INITIAL</tt>.
   *
   * @param reader   the new input stream 
   */
  public final void yyreset(java.io.Reader reader) {
    zzReader = reader;
    zzAtBOL  = true;
    zzAtEOF  = false;
    zzEOFDone = false;
    zzEndRead = zzStartRead = 0;
    zzCurrentPos = zzMarkedPos = 0;
    yyline = yychar = yycolumn = 0;
    zzLexicalState = YYINITIAL;
  }


  /**
   * Returns the current lexical state.
   */
  public final int yystate() {
    return zzLexicalState;
  }


  /**
   * Enters a new lexical state
   *
   * @param newState the new lexical state
   */
  public final void yybegin(int newState) {
    zzLexicalState = newState;
  }


  /**
   * Returns the text matched by the current regular expression.
   */
  public final String yytext() {
    return new String( zzBuffer, zzStartRead, zzMarkedPos-zzStartRead );
  }


  /**
   * Returns the character at position <tt>pos</tt> from the 
   * matched text. 
   * 
   * It is equivalent to yytext().charAt(pos), but faster
   *
   * @param pos the position of the character to fetch. 
   *            A value from 0 to yylength()-1.
   *
   * @return the character at position pos
   */
  public final char yycharat(int pos) {
    return zzBuffer[zzStartRead+pos];
  }


  /**
   * Returns the length of the matched text region.
   */
  public final int yylength() {
    return zzMarkedPos-zzStartRead;
  }


  /**
   * Reports an error that occured while scanning.
   *
   * In a wellformed scanner (no or only correct usage of 
   * yypushback(int) and a match-all fallback rule) this method 
   * will only be called with things that "Can't Possibly Happen".
   * If this method is called, something is seriously wrong
   * (e.g. a JFlex bug producing a faulty scanner etc.).
   *
   * Usual syntax/scanner level error handling should be done
   * in error fallback rules.
   *
   * @param   errorCode  the code of the errormessage to display
   */
  private void zzScanError(int errorCode) {
    String message;
    try {
      message = ZZ_ERROR_MSG[errorCode];
    }
    catch (ArrayIndexOutOfBoundsException e) {
      message = ZZ_ERROR_MSG[ZZ_UNKNOWN_ERROR];
    }

    throw new Error(message);
  } 


  /**
   * Pushes the specified amount of characters back into the input stream.
   *
   * They will be read again by then next call of the scanning method
   *
   * @param number  the number of characters to be read again.
   *                This number must not be greater than yylength()!
   */
  public void yypushback(int number)  {
    if ( number > yylength() )
      zzScanError(ZZ_PUSHBACK_2BIG);

    zzMarkedPos -= number;
  }


  /**
   * Resumes scanning until the next regular expression is matched,
   * the end of input is encountered or an I/O-Error occurs.
   *
   * @return      the next token
   * @exception   java.io.IOException  if any I/O-Error occurs
   */
  public Tokens yylex() throws java.io.IOException {
    int zzInput;
    int zzAction;

    // cached fields:
    int zzCurrentPosL;
    int zzMarkedPosL;
    int zzEndReadL = zzEndRead;
    char [] zzBufferL = zzBuffer;
    char [] zzCMapL = ZZ_CMAP;

    int [] zzTransL = ZZ_TRANS;
    int [] zzRowMapL = ZZ_ROWMAP;
    int [] zzAttrL = ZZ_ATTRIBUTE;

    while (true) {
      zzMarkedPosL = zzMarkedPos;

      zzAction = -1;

      zzCurrentPosL = zzCurrentPos = zzStartRead = zzMarkedPosL;
  
      zzState = ZZ_LEXSTATE[zzLexicalState];


      zzForAction: {
        while (true) {
    
          if (zzCurrentPosL < zzEndReadL)
            zzInput = zzBufferL[zzCurrentPosL++];
          else if (zzAtEOF) {
            zzInput = YYEOF;
            break zzForAction;
          }
          else {
            // store back cached positions
            zzCurrentPos  = zzCurrentPosL;
            zzMarkedPos   = zzMarkedPosL;
            boolean eof = zzRefill();
            // get translated positions and possibly new buffer
            zzCurrentPosL  = zzCurrentPos;
            zzMarkedPosL   = zzMarkedPos;
            zzBufferL      = zzBuffer;
            zzEndReadL     = zzEndRead;
            if (eof) {
              zzInput = YYEOF;
              break zzForAction;
            }
            else {
              zzInput = zzBufferL[zzCurrentPosL++];
            }
          }
          int zzNext = zzTransL[ zzRowMapL[zzState] + zzCMapL[zzInput] ];
          if (zzNext == -1) break zzForAction;
          zzState = zzNext;

          int zzAttributes = zzAttrL[zzState];
          if ( (zzAttributes & 1) == 1 ) {
            zzAction = zzState;
            zzMarkedPosL = zzCurrentPosL;
            if ( (zzAttributes & 8) == 8 ) break zzForAction;
          }

        }
      }

      // store back cached position
      zzMarkedPos = zzMarkedPosL;

      switch (zzAction < 0 ? zzAction : ZZ_ACTION[zzAction]) {
        case 4: 
          { lexeme=yytext(); return ID;
          }
        case 13: break;
        case 12: 
          { lexeme=yytext(); return ListaParam;
          }
        case 14: break;
        case 11: 
          { lexeme=yytext(); return Retorno;
          }
        case 15: break;
        case 5: 
          { lexeme=yytext(); return Reservadas;
          }
        case 16: break;
        case 8: 
          { lexeme=yytext(); return Tipo;
          }
        case 17: break;
        case 7: 
          { lexeme=yytext(); return TipoPrimitivo;
          }
        case 18: break;
        case 9: 
          { lexeme=yytext(); return Param;
          }
        case 19: break;
        case 2: 
          { lexeme=yytext(); return Numero;
          }
        case 20: break;
        case 3: 
          { lexeme=yytext(); return Enter;
          }
        case 21: break;
        case 6: 
          { /*Ignore*/
          }
        case 22: break;
        case 1: 
          { lexeme=yytext(); return Simbolo;
          }
        case 23: break;
        case 10: 
          { lexeme=yytext(); return DeclaracaoVar;
          }
        case 24: break;
        default: 
          if (zzInput == YYEOF && zzStartRead == zzCurrentPos) {
            zzAtEOF = true;
            return null;
          } 
          else {
            zzScanError(ZZ_NO_MATCH);
          }
      }
    }
  }


}
