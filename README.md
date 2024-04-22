# csse332-sp2324-review-session2
## How to download and edit the files here:
First, create a new directory on your WSL. You can do this by running the following command:
``` 
mkdir <directory name>
```
Once you've done that, go ahead and cd into the directory. Then, you'll want to go ahead and run the following command:
```
git clone git@github.com:wynessgp/csse332-sp2324-review-session2.git
```
And that should go ahead and move all of the files over to your WSL. My suggestion is you keep all the review sessions material in this directory, as they'll be nicely organized. Note that you could also just directly clone this repo from your home directory, and the file that comes out of that will just be the repo's name. 

If you are having errors with GitHub saying it cannot authenticate you due to a publickey issue, you'll need to create a SSH key. You can either follow the instructions on [GitHub's website](https://docs.github.com/en/authentication/connecting-to-github-with-ssh/generating-a-new-ssh-key-and-adding-it-to-the-ssh-agent) to generate one, or you can follow Comp Arch 1's tutorial [here](comp-arch-ssh-tutorial.md). Note that the Comp Arch 1 tutorial talks about using `Git Bash` -- you'll need to do all of those steps in WSL instead, so do it on your Ubuntu machine! 

If that is not the error, I'd suggest following whatever the console spits out - those hints usually tell you everything you need.

I'd recommend leaving this README page up on [GitHub](https://github.com/wynessgp/csse332-sp2324-review-session2) and tabbing back and forth for instructions. If you are viewing this in VSCode, note that to render markdowns, you can do `Ctrl + k, v` (in that order), although you shouldn't ever open VSCode for this class (you certainly won't be allowed to on the Exams). I have tried to leave you some nice links that you can click on for some navigability.

## A quick request
If you are going to ask me questions related to this practice exam after the review session, please see me for my regularly scheduled hours within the next 2 weeks:

- Wednesday, April 24th, Percopo Classroom
- Thursday, April 25th, Percopo 2 Study Room (Speed side)
- Monday, April 29th, Percopo Classroom
- Thursday, May 2nd, Percopo 2 Study Room (Speed side)

All hours are from 7-10pm. 

I am not sure how busy my week 7 will be, so if you do have questions outside of these regular hours, you can send me a message on Teams. 

I cannot guarantee that I'll respond, or I may just tell you I don't have time, but you are welcome to send me messages.

<a id="toc"></a>

## Table of Contents

Brief reminder that these links will only work if you're viewing this file in a markdown renderer, or if you're viewing this on GitHub. I would highly recommend using one of those!

[Administrative Notes](#admin_notes) <br>
[Content Notes](#content_notes) <br>
[Problem 1](#problem_one) <br>
[Problem 2](#problem_two) <br>
[Problem 3](#problem_three) <br>

<a id="admin_notes"></a>

## Administrative Notes 
The GitHub repository will only contain the **questions** for this practice exam. I **will not** be posting **solutions** here as I find it is a little too easy to just flip back and forth between the two and not really do any practice or learn much. 

If you find that having the solutions would really help you out, you are welcome to reach out to me via Teams or via email(wynessgp@rose-hulman.edu) 

If you find that these questions are a little challenging, that's good - I do this on purpose, as I find that if you can solve these, you should be ready for 99% of the questions they can throw at you on the exams.

That being said, here's the schedule for your exams, split into two parts like Exam 1:
- Part 1 will be on Friday, 4/26, during your regularly scheduled class time.
- Part 2 will be on Friday, 5/3, during your regularly scheduled class time. 

Since these are both held during regular class time, you will have `50` minutes on each portion of the exam, if you do not have accomodations. The time crunch is both a major aspect of the exam AND determines how difficult the questions can realistically be.

Be careful with studying some of the older exams that have been released, as these were `3` hour long night exams. If the year on the practice exam you're looking at isn't '23-'24, then it was a `3`-hour long night exam. 

On the two separate parts of this exam, you should anticipate getting two questions on each part. As far as a credit breakdown goes for each part:
- Question 1: Basics of the given concept. Usually enough to earn a C for this portion of the exam if you get this correct.
- Question 2: More advanced side of the concept. You will need to get both parts correct to earn an A.

As they did with Exam 1, both parts of this exam will count towards your overall exam grade. So if you manage to get a 100% on one of the parts, but get a 0% on the second part, the most you're elgible for is a 50/100. They are equally weighted. Do your best!

Another thing to note about this exam - you'll be connecting to a remote server for this exam (at least on coding portions, I don't know if there will be a paper one), so you'll have to use `ssh` in order to even see the exam files. 

In particular, this means any modifications you've made to your `vim` config or the like will not carry over to this new machine you'll be on. This means you won't have access to your local `git` repo unless if your professor allows you to bring it over. 

If these changes affect you, I'd highly recommend logging onto the server ahead of time to change your config!

<a id="content-notes"></a>

## *Content* Notes

