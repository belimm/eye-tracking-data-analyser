# eye-tracking-data-analyser
Data analyzer by using heap data structure and heap sort algorithm.


<h2>Motivation</h2>

Eye tracking is commonly used to understand how people interact with visual stimuli. When people interact with web pages, their eyes become relatively stable at certain points referred to as fixations. The series of these fixations represent their scan paths. Eye-tracking data analysis is typically conducted based on the areas of interest (AOIs) of visual stimuli, specifically which AOIs are commonly used and in which order. Figure 1 shows an example of a person's eye-tracking data on one page of the WordPress.com website, which is segmented into its AOIs, where the fixations are represented as circles and the longer fixations are represented with the larger circles.




In this project, simple eye-tracking data analyser which supports the following functionalities:

<h2>Functional Requirements</h2>
1) Take a series of fixations of multiple people on a particular page (id, x, y, the duration for each fixation)
2) Take the details of the AOIs of the page (name, top-left-x, width, top-left-y, and height)
3) Compute the total number of fixations (i.e. fixation count) and the total duration of fixations
(i.e. dwell time) for each AOI.
4) Sort the AOIs based on either fixation count or dwell time
5) Print the sorted AOIs with their fixation counts and dwell time

<h2>Figures</h2>

<img width="799" alt="image" src="https://user-images.githubusercontent.com/76854271/156813875-739503e3-fb67-4588-963d-b4a68f9d2ed4.png">
<img width="746" alt="image" src="https://user-images.githubusercontent.com/76854271/156813889-2af1278e-0e1f-4b10-bbae-143381c053bd.png">
<img width="939" alt="image" src="https://user-images.githubusercontent.com/76854271/156813937-698d496a-e31e-47dc-8069-62f745526216.png">
<img width="989" alt="image" src="https://user-images.githubusercontent.com/76854271/156813967-0ac2bd00-df45-4c47-bb2d-e4ba77816eaf.png">


<h2>Sample Output</h2>

<img width="383" alt="image" src="https://user-images.githubusercontent.com/76854271/156813995-7638b055-7257-409a-b1f4-f1c1ce33fe7d.png">
