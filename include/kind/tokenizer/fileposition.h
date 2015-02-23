#ifndef _KIND_TOKENIZER_FILEPOSITION
#define _KIND_TOKENIZER_FILEPOSITION

namespace kind
{
    namespace tokenizer
    {
        class FilePosition
        {
        private:
            int row, column;
            int lastRow, lastColumn;
        public:
            FilePosition ()
                : FilePosition (1,0)
            {
            }
            FilePosition (int row, int column)
                : row(row), column(column)
            {
            }
            
            int lineNumber() { return row; }
            int columnNumber() { return column; }
            void advance (int ch)
            {
                lastRow = row;
                lastColumn = column;
                if (ch == '\n')   
                {
                    row ++;
                    column = 0;
                }
                else
                {
                    column ++;
                }
            }
            void retreat ()
            {
                row = lastRow;
                column = lastColumn;
            }
        };
        
    }
}

#endif
