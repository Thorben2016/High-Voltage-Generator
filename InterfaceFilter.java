package HighVoltageGeneratorInterface;

import javax.swing.text.*;

@SuppressWarnings("serial")

  
   public class InterfaceFilter extends DocumentFilter {
      private int maxNumber;
      private int maxCharacters;    
      

      public InterfaceFilter(int maxnumber, int maxChars) {
         maxNumber = maxnumber;
         maxCharacters = maxChars;
      }

      private boolean verifyText(String text) {
         if (text.isEmpty()) {
            return true; // allow for a blank text field
         }
         int value = 0;
         try {
            value = Integer.parseInt(text);
            if (value >= 0 && value < maxNumber) {
               return true; // if it's a number in range, it passes
            }
         } catch (NumberFormatException e) {
            return false;  // if it's not a number, it fails.
         }
         return false;
      }

      @Override
      public void insertString(DocumentFilter.FilterBypass filter, int os, String str,
               AttributeSet attr) throws BadLocationException {

         Document doc = filter.getDocument();
         String oldText = doc.getText(0, doc.getLength());
         StringBuilder sb = new StringBuilder(oldText);
         sb.insert(os, str);

         if (verifyText(sb.toString()) && (filter.getDocument().getLength() + str.length()) <= maxCharacters) {
            super.insertString(filter, os, str, attr);
            
         }
         
      }

      @Override
      public void replace(DocumentFilter.FilterBypass filter, int os, int length, String text, AttributeSet attrs)
               throws BadLocationException {
          
         Document doc = filter.getDocument();
         String oldText = doc.getText(0, doc.getLength());
         StringBuilder sb = new StringBuilder(oldText);

         sb.replace(os, os + length, text);
         if (verifyText(sb.toString()) && (filter.getDocument().getLength() + text.length()
                - length) <= maxCharacters) {
            super.replace(filter, os, length, text, attrs);
            
            
         }
         
      }

      @Override
      public void remove(DocumentFilter.FilterBypass filter, int os, int length) throws BadLocationException {
         Document doc = filter.getDocument();
         String oldText = doc.getText(0, doc.getLength());
         StringBuilder sb = new StringBuilder(oldText);

         sb.replace(os, os + length, "");

         if (verifyText(sb.toString())) {
            super.remove(filter, os, length);            
         }
      }
   

   
}