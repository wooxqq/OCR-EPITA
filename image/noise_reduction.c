/* Noise reduction X4 for the moment...*/
void noiseReduction(SDL_Surface *img)
{
  /* Variables */
  int w;
  int h;
  w = img -> w;
  h = img -> h;
  int pixelTable[4];

 for(int i = 0; i < w; i++)
 {
   for(int j = 0; j < h; j++)
   {
     for(int k = j; k <= j + 4; k++)
     {
       //Borders of picture
       if(i == 0)
       {
         if(k == 0)
         {
            pixelTable[0] = getpixel(img, i, k);
            pixelTable[1] = getpixel(img, i, k);
            pixelTable[2] = getpixel(img, i, k);
            pixelTable[3] = getpixel(img, i, k + 1);
            pixelTable[4] = getpixel(img, i + 1, k);
            break;
         }
         if(k == h)
         {
            pixelTable[0] = getpixel(img, i, k);
            pixelTable[1] = getpixel(img, i, k - 1);
            pixelTable[2] = getpixel(img, i, k);
            pixelTable[3] = getpixel(img, i, k);
            pixelTable[4] = getpixel(img, i + 1, k);
            break;
         }
         else
         {
          pixelTable[0] = getpixel(img, i, k);
          pixelTable[1] = getpixel(img, i, k - 1);
          pixelTable[2] = getpixel(img, i, k);
          pixelTable[3] = getpixel(img, i, k + 1);
          pixelTable[4] = getpixel(img, i + 1, k);
          break;
         }
       }
       if(i == w)
       {
          if(k == 0)
          {
            pixelTable[0] = getpixel(img, i, k);
            pixelTable[1] = getpixel(img, i, k);
            pixelTable[2] = getpixel(img, i - 1, k);
            pixelTable[3] = getpixel(img, i, k + 1);
            pixelTable[4] = getpixel(img, i, k);
            break;
          }
          if(k == h)
          {
            pixelTable[0] = getpixel(img, i, k);
            pixelTable[1] = getpixel(img, i, k - 1);
            pixelTable[2] = getpixel(img, i - 1, k);
            pixelTable[3] = getpixel(img, i, k);
            pixelTable[4] = getpixel(img, i, k);
            break;
          }
          else
          {
            pixelTable[0] = getpixel(img, i, k);
            pixelTable[1] = getpixel(img, i, k - 1);
            pixelTable[2] = getpixel(img, i - 1, k);
            pixelTable[3] = getpixel(img, i, k + 1);
            pixelTable[4] = getpixel(img, i, k);
            break;
          }
       }
       if(k == 0)
       {
          pixelTable[0] = getpixel(img, i, k);
          pixelTable[1] = getpixel(img, i, k);
          pixelTable[2] = getpixel(img, i - 1, k);
          pixelTable[3] = getpixel(img, i, k + 1);
          pixelTable[4] = getpixel(img, i + 1, k);
          break;
       }
       if(k == h)
       {
        pixelTable[0] = getpixel(img, i, k);
        pixelTable[1] = getpixel(img, i, k - 1);
        pixelTable[2] = getpixel(img, i - 1, k);
        pixelTable[3] = getpixel(img, i, k);
        pixelTable[4] = getpixel(img, i + 1, k);
        break;
       }
       else
       {
        pixelTable[0] = getpixel(img, i, k);
        pixelTable[1] = getpixel(img, i, k - 1);
        pixelTable[2] = getpixel(img, i - 1, k);
        pixelTable[3] = getpixel(img, i, k + 1);
        pixelTable[4] = getpixel(img, i + 1, k);
        break;
       }
     }
      array_select_sort(pixelTable, 5);
      int med = pixelTable[2];
      putpixel(img, i, j, med);
   }
 }
}
