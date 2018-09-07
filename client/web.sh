#!/bin/bash

cars__=$(ls -1 | grep ^cars ) # 0
dogs__=$(ls -1 | grep ^dogs ) # 1
cats__=$(ls -1 | grep ^cats ) # 2
trucks__=$(ls -1 | grep ^trucks ) # 3

n_cars=$(ls -1 | grep ^cars | wc -l)
n_dogs=$(ls -1 | grep ^dogs | wc -l)
n_cats=$(ls -1 | grep ^cats | wc -l)
n_trucks=$(ls -1 | grep ^trucks | wc -l)

declare -A Ht

Ht=( ["Cars"]="0" ["Dogs"]="2" ["Cats"]="1" ["Trucks"]="3" )


init(){
  c=0
  for i in $@
  do
	  if [[ ! $i -eq "0" ]];then
		echo "showSlides(1, $c)"
	  fi
	  c=$((c+1))
  done
}

div(){
  if [[ -z $2 ]]; then
	echo "<!-- No $1 section -->"
  else
	f=$1
	i=$1
  	echo "<p>$i</p>"
	shift
  	echo "  <div class=\"slideshow-container\">"
	  for i in $@
          do
  	  if [[ ! -z $i ]]; then
  	  	echo "  <div class=\"$f\">"
		echo 	"  <img src=\"$i\" style=\"width:100%\">"
  	  	echo "  </div>"
  	  fi
	  done
  	  echo ""
  	  echo "  <a class=\"prev\" onclick=\"plusSlides(-1, ${Ht[$f]})\">&#10094;</a>"
  	  echo "  <a class=\"next\" onclick=\"plusSlides(1, ${Ht[$f]})\">&#10095;</a>"
  	echo "  </div>"
  fi
}

cat <<- _EOF_

  <!DOCTYPE html>
  <html>
  <head>
  <meta name="viewport" content="width=device-width, initial-scale=1">
  <style>
  * {box-sizing: border-box}
  .mySlides1, .mySlides2 {display: none}
  img {vertical-align: middle;}
  
  /* Slideshow container */
  .slideshow-container {
    max-width: 1000px;
    position: relative;
    margin: auto;
  }
  
  /* Next & previous buttons */
  .prev, .next {
    cursor: pointer;
    position: absolute;
    top: 50%;
    width: auto;
    padding: 16px;
    margin-top: -22px;
    color: white;
    font-weight: bold;
    font-size: 18px;
    transition: 0.6s ease;
    border-radius: 0 3px 3px 0;
    user-select: none;
  }
  
  /* Position the "next button" to the right */
  .next {
    right: 0;
    border-radius: 3px 0 0 3px;
  }
  
  /* On hover, add a grey background color */
  .prev:hover, .next:hover {
    background-color: #f1f1f1;
    color: black;
  }
  </style>
  </head>
  <body>
  
  <h2 style="text-align:center">Multiple Slideshows</h2>
  
  $(div "Cars" $cars__)
  
  $(div "Cats" $cats__)
  
  $(div "Dogs" $dogs__)

  $(div "Trucks" $trucks__)
  
  <script>
  var slideIndex = [1,1,1,1];
  var slideId = ["Cars", "Cats", "Dogs", "Trucks"]
  $(init n_cars n_cats n_dogs n_trucks)
  
  function plusSlides(n, no) {
    showSlides(slideIndex[no] += n, no);
  }
  
  function showSlides(n, no) {
    var i;
    var x = document.getElementsByClassName(slideId[no]);
    if (n > x.length) {slideIndex[no] = 1}
    if (n < 1) {slideIndex[no] = x.length}
    for (i = 0; i < x.length; i++) {
       x[i].style.display = "none";
    }
    x[slideIndex[no]-1].style.display = "block";
  }
  </script>
  
  </body>
  </html>


_EOF_



### use  ./web.sh $number_of_images > file.html
