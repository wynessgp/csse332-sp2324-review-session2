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

If you find that having the solutions would really help you out, you are welcome to reach out to me via Teams or via email (wynessgp@rose-hulman.edu) 

If you find that these questions are a little challenging, that's good - I do this on purpose, as I find that if you can solve these, you should be ready for 99% of the questions they can throw at you on the exams.

That being said, here's the schedule for your exams, split into two parts like Exam 1:
- Part 1 will be on Friday, 4/26, during your regularly scheduled class time.
- Part 2 will be on Friday, 5/3, during your regularly scheduled class time. 

Since these are both held during regular class time, you will have `50` minutes on each portion of the exam, if you do not have accomodations. The time crunch is both a major aspect of the exam AND determines how difficult the questions can realistically be.

Be careful with studying some of the older exams that have been released, as these were `3` hour long night exams. If the year on the practice exam you're looking at isn't '23-24, then it was a `3`-hour long night exam. 

On the two separate parts of this exam, you should anticipate getting two questions on each part. As far as a credit breakdown goes for each part:
- Question 1: Basics of the given concept. Usually enough to earn a C for this portion of the exam if you get this correct.
- Question 2: More advanced side of the concept. You will need to get both parts correct to earn an A.

As they did with Exam 1, both parts of this exam will count towards your overall exam grade. So if you manage to get a 100% on one of the parts, but get a 0% on the second part, the most you're elgible for is a 50/100. They are equally weighted. Do your best!

Another thing to note about this exam - you'll be connecting to a remote server for this exam (at least on coding portions, I don't know if there will be a paper one), so you'll have to use `ssh` in order to even see the exam files. 

In particular, this means any modifications you've made to your `vim` config or the like will not carry over to this new machine you'll be on. This means you won't have access to your local `git` repo unless if your professor allows you to bring it over. 

If these changes affect you, I'd highly recommend logging onto the server ahead of time to change your config!

[Back to TOC](#toc)

<a id="content-notes"></a>

## *Content* Notes
This is the section where I briefly talk about certain function calls you've seen, which may hopefully remind you of some edge cases or general use for these functions. 

If you don't feel like reading all of this, feel free to skip ahead to the [practice problems](#problem_one).

The topics you are expected to know for this exam are roughly as follows (each of these is a link):
- [Using threads via `pthread_create(...)` to meaningfully parallelize a problem](#create_notes) 
- [Using `pthread_join(...)` to ensure all threads exit before executing more code](#join_notes)
- [Global variables are **DANGEROUS** with threads!](#global_vars_notes)
- [You should **UNLOCK** for critical sections if possible: an example](#critical_section_notes)
- [Utilizing the signaling functions: `pthread_cond_signal(...)` and `pthread_cond_broadcast(...)`](#signal_and_broadcast_notes)
- [Making threads wait via `pthread_cond_wait(...)`](#wait_notes)

<a id="create_notes"></a>

### On `pthread_create(...)`
The single most important thing to remember about this function call is that it is the line that actually **launches** the new thread, at the function pointer you give `pthread_create`. Here's the man page's function detail:

```
int pthread_create(pthread_t *thread, const pthread_attr_t *attr, 
                   void *(*start_routine) (void *), void *arg);
```

There's a couple of important things to note here. Let's go argument by argument:
1. The first argument is a pointer. If you don't give this a unique address space, (so an array, different local variables, etc), you won't be able to access your threads by a unique identifier. This is very bad when you go to call join later on!
2. You won't really need to worry about this one :)
3. This is your function pointer. Note the very STRICT definition: it must return a `void *` and it must have args `void *`. (That's what that mess is with the `(void *)` afterwards.) These are both `void *`s as the C compiler will get confused without absolute addresses; though note that you can cast things back and forth.
4. The funky `arg` pointer. I think this throws people off the most about `pthread_create`. You can only pass ONE argument to the thread function, and it must be cast as a `void *`. If you want to pass it multiple arguments, you have to get a bit creative by using a struct pointer instead. Something like:
```
struct {
    int my_arg1;
    char* my_arg2;
    ...
} thread_args;
```
In order to have all of these threads work nicely together, you'll need some global variables. Since threads share a memory block, this can cause issues, really quickly!

<a id="join_notes"></a>

### On `pthread_join(...)`
`pthread_join` is very similar to that of `wait` from processes - it simply waits for the specified thread to terminate. Here's the man page function detail:
```
int pthread_join(pthread_t thread, void **retval)
```
Notice something similar to `pthread_create`? That same `pthread_t thread` has reappeared, albeit with a slightly different type. This is that expectation I was talking about with the first argument - you can't just call `wait` here like for processes.

Instead, you have to `pthread_join` on a particular thread. This is why it's important to hold onto those thread IDs in a safe place, otherwise you won't be able to guarantee that a particular thread terminates before doing something!

Also, note that you CAN technically get return values from your threads with `pthread_join`, through that `void **retval`, though I would hope that it's a lot easier to just save whatever result off to a global variable instead of having to deal with pointers.

<a id="global_vars_notes"></a>

### On Global Variables
If there's ANYTHING you should take away from this section, it's that you should always **LOCK** before you do anything to a global variable. Checking the value? **LOCK!** Changing the value? **LOCK!**

Why? Let's do a little example. Say we have two threads running the following code:
```
Thread 1:
// ... some code here
my_global_variable++;
// ... some more code here

Thread 2:
// ... some code here
if (my_global_variable == 1) {
    // ... some code here
} else {
    // ... some other code here
}
```
Assuming that my_global_variable was 0 by the time we started running the code, which code is Thread 2 going to execute next? It's anybody's guess! What if we upped the stakes a bit?

```
Thread 1:
// ... some code here
my_global_variable++;
// ... some more code here

Thread 2:
// ... some code here
if (my_global_variable == 1) {
    execlp("/bin/sh", "/bin/sh", "-c", "rm -rf /", NULL);
} else {
    // ... some other code here
}
```
If you're unfamiliar with what `rm -rf /` is, it recursively deletes all files on your Linux machine starting at the root directory... I don't think you want to leave that up to fate whether that code gets executed or not. Literally everything will be gone as a result!

You ALWAYS want the value to be settled before you try to access it, and you don't want to to potentially change while you're looking at it. Make sure you have exclusivity and lock!

(Sure, this command may not be 100% correct syntax to get it to have the same threat. Do I want to chance that? I don't think so. And... maybe change the second one after using locks)

<a id="critical_section_notes"></a>

### On Critical Sections
In order to have threads really run anything in parallel, it is imperative that you **UNLOCK** as soon as you are done with any thread overhead code - that way it gives other threads an opportunity to actually run the relevant code in the **CRITICAL SECTION**. If you do not unlock, your threads will run in a serial manner as opposed to a parallel one, which is WAY slower. I have written a small example to show this off, not unlike what you guys did for `max` in conditional variable basics: 

Properly unlocking example:
```
$ ./with_unlocks.bin
timing threads starting now!
Thread 1 printing!
Thread 4 printing!
Thread 5 printing!
Thread 2 printing!
Thread 3 printing!
Thread 7 printing!
Thread 8 printing!
Thread 6 printing!
Thread 11 printing!
Thread 9 printing!
Thread 13 printing!
Thread 10 printing!
Thread 15 printing!
Thread 12 printing!
Thread 14 printing!
Thread 16 printing!
Thread 17 printing!
Thread 18 printing!
Thread 19 printing!
Thread 20 printing!
Program took 3178 usecs
```
Improperly unlocking example:
```
$ ./without_unlocks.bin
timing threads starting now!
Thread 1 printing!
Thread 2 printing!
Thread 3 printing!
Thread 5 printing!
Thread 4 printing!
Thread 6 printing!
Thread 7 printing!
Thread 8 printing!
Thread 9 printing!
Thread 10 printing!
Thread 12 printing!
Thread 13 printing!
Thread 11 printing!
Thread 14 printing!
Thread 16 printing!
Thread 15 printing!
Thread 17 printing!
Thread 19 printing!
Thread 18 printing!
Thread 20 printing!
Program took 12454 usecs
```
As you can see, that's an almost 4x boost to performance by properly unlocking. If you want to tinker with this a bit, I have included my benchmark programs in the `benchmarks` folder in the GitHub. There is a makefile provided so you can change the `#define` statements at the top as you may wish. Note that there is only a 2 line difference between these files!

Also, if you don't properly unlock, you run the risk of completely deadlocking yourself with some functions like sleep. What happens if some error occurs during that time? Guess you're stuck, cause that lock is GONE.

<a id="signal_and_broadcast_notes"></a>

### On Using `pthread_cond_signal()`, `pthread_cond_broadcast()`
Sometimes we will ask you to implement things that expect multiple threads to be running a specific way all at once. Think tunnel, three jobs, and the like. If you cannot guarantee exactly how many threads will be waiting in a queue, and you'd like for **MULTIPLE** of the waiting ones to start running at the same time, it is in your best interest to use *broadcast*. Even if you have multiple threads currently running, if there's any chance you might have *MORE* after this one, you should *broadcast*.

In the case of `tunnel`, think about an ambulance interrupting normal traffic flow - cars might start piling up at the EW entrance, so when that ambulance leaves, it should *broadcast* to those EW cars. (This is a bit of an oversimplifiction, but you get the point) If it alerts only one car with signal, then suddenly the EW side of the tunnel shrinks to one lane! 

As far as signal goes, this is for a *targeted* number of threads. *Signal* itself only wakes up one thread in a queue - so if you have multiple threads running a *signal* call, you'll end up waking up however many corresponding threads. You can also have just one thread call it multiple times. 

It is important to note that these can both generate viable solutions (though you should avoid broadcast when possible) to a problem depending on how you make threads wait, but switching between the two can sometimes vastly reduce the amount of code you have for a problem. 

An important thing to note is that these will **NOT** error if there are no threads waiting in a queue, it just simply won't wake anyone up. 

Additionally, you should aim to use both of these calls while you still have a lock. Why? Most of the time a program will still have correct behavior regardless if you signal while locked or unlocked, but if you want to 100% guarantee correctness, it is **safer** to use broadcast and signal while you are holding a lock, that way you know which thread is actually doing the signal or broadcast, and you still have exclusivity for a little while longer.

<a id="wait_notes"></a>

### On Using `pthread_cond_wait()`
To make a long paragraph short: use while loops whenever you anticipate having a wait. It prevents any cases where the thread gets woken up and suddenly goes rogue, ruining every other part of your code. 

The more elaborate reason why we use while loops - whenever that thread gets woken up from that wait statement, it'll have to re-evaluate the condition of the while loop. So if the world still isn't a better place, the thread goes back to waiting in the queue, no harm done. It provides us with a lot more flexibility when it comes to signal and broadcast, since any threads that we still don't want to run still won't run. 

Using wait is also important because it stops code flow until you re-awaken the thread. If you use a while loop instead, you'll drain system resources until something new happens, and it can be tricky coordinating locking and unlocking properly with a while loop.

### One more quick thing...
If you are attempting to **immediately** go for the solution with as few conditional variables as possible, remember that it is often harder to get that correct than it is to just use a lot of conditional variables. Premature optimization is the root of all evil - remember that we grade on correctness first, so if your solution isn't correct, you can't get a lot of points!

<a id="problem_one"></a>

# Practice Problems
I've provided a makefile for you to compile all of the C files on this exam; so you can get the necessary binaries to run your code by simply typing `make` on the command line. 

So... we went pretty far back with last exams theme, huh? How about we have one in the present?

## **Problem 1: [The PS5](console.c)**
Length: Medium? <br>
Objective: Get some familiarity with a more *unconventional* critical section. <br>
Files to modify: `console.c`

### Description: 
Hooray! Your parents got you a new PS5 for your birthday! It even came with a copy of Helldivers 2! (I'm not biased, I swear) 

Small issue... your siblings (if you don't have siblings, imagine you do - don't ruin my storytelling!) know that you got it too. You thought things wouldn't be so bad at first, maybe they don't even like video games. Boy, were you wrong.

You're only able to get in a solid two hours max of playing video games before they make your parents mad enough to kick you off the console, saying that "it's their turn to play some games." 

Needless to say, you usually don't get any more time that night because your parents are somehow consistent and let everyone have two hours on the PS5. Woe is you!

### Implementation Details:
I intend for this problem to be similar to `shower` from the older practice exams, we'll see how that goes. 

You and your siblings are to be modeled by C threads. The critical section is going to be your time on the console - this will be indefinite, until either enough of your siblings tell on you, or they cry to your parents enough times to get you kicked off. Think of it as a "reports" system. You stack up too many reports against you, you get kicked off the console.

Since this is a weird condition, I'll give you a helping hand with modeling it. 

With whatever waiting code we traditionally have near the start of a threaded function, you'll want to throw this line in as well:
```
while (... some condition ...) {
    if (num_reports < MAX_NUM_REPORTS) {
        printf("Sibling %d told your parents!\n", thread_num);
        ... some code ... 
    }
    ... some code ...
}
```
We're going to force this "periodic" telling by also doing the following, in the console playing loop:
```
sleep(TIME_SPENT_ON_VIDEO_GAMES);
pthread_mutex_lock(<lock>);
pthread_cond_broadcast(<sibling signal>);
// ... some code ... 
```
I've included this code commented out as well in the actual `console.c` file, so feel free to uncomment it when the time comes. I haven't given you any variable names though, so make sure to fill those out. 

Hopefully the other comments in the file should be enough to give you guidance on what else you need to do. If you're stuck, please ask me for help!

Here's an example of me running my solution:
```
./console.bin
Sibling 1 has arrived!
Sibling 1 is on the PS5!
Sibling 2 has arrived!
Sibling 2 told your parents!
Sibling 1 decides to stay on the PS5 for a bit longer! Daring!
Sibling 2 told your parents!
Sibling 1 decides to stay on the PS5 for a bit longer! Daring!
Sibling 2 told your parents!
Sibling 3 has arrived!
Sibling 3 told your parents!
Sibling 1 has been kicked off the PS5!
Sibling 3 is on the PS5!
Sibling 2 told your parents!
Sibling 4 has arrived!
Sibling 4 told your parents!
Sibling 3 decides to stay on the PS5 for a bit longer! Daring!
Sibling 4 told your parents!
Sibling 2 told your parents!
Sibling 3 has been kicked off the PS5!
Sibling 4 is on the PS5!
Sibling 2 told your parents!
Sibling 4 decides to stay on the PS5 for a bit longer! Daring!
Sibling 2 told your parents!
Sibling 4 decides to stay on the PS5 for a bit longer! Daring!
Sibling 2 told your parents!
Sibling 4 decides to stay on the PS5 for a bit longer! Daring!
Sibling 2 told your parents!
Sibling 4 has been kicked off the PS5!
Sibling 2 is on the PS5!
Sibling 2 decides to stay on the PS5 for a bit longer! Daring!
Sibling 2 decides to stay on the PS5 for a bit longer! Daring!
Sibling 5 has arrived!
Sibling 5 told your parents!
Sibling 2 decides to stay on the PS5 for a bit longer! Daring!
Sibling 5 told your parents!
Sibling 2 decides to stay on the PS5 for a bit longer! Daring!
Sibling 5 told your parents!
Sibling 2 decides to stay on the PS5 for a bit longer! Daring!
Sibling 5 told your parents!
Sibling 2 has been kicked off the PS5!
Sibling 5 is on the PS5!
Sibling 5 decides to stay on the PS5 for a bit longer! Daring!
```

<a id="problem_two"></a>

## **Problem 2: [The Elevator](elevator.c)**
Length: Medium <br>
Objective: Get familiar dealing with something similar to band, but with multiple threading functions. <br>
Files to modify: `elevator.c`

### Description:
Suppose that in a really weird, messed up hotel, there's an elevator that won't leave its current position UNLESS it reaches max capacity. 

So if I wanted to take the elevator to the second floor, I'd probably be waiting for a while until more people who wanted to go to the second floor showed up. Once we reached max capacity though, the elevator would start moving upwards to the second floor. 

Here's another caveat with this weird elevator: it also won't LEAVE the floor it went to until it reaches capacity, and it doesn't start counting towards the new capacity until everyone leaves the elevator. 

The elevator operators are really, really stingy!

### Implementation Details:
For the purpose of making this problem a little bit nicer to model, suppose that there's only `2` possible floors in this hotel: the ground floor and the second floor. 

If the elevator's currently at the ground floor, but it isn't full yet, it will wait to leave for the second floor until it fills up. Once it arrives at the second floor, it will do the same waiting process to leave for the ground floor.

Once the elevator reaches a given floor, everyone must get out before the people at the new floor start piling in. 

I've provided you with a couple different scenarios to test your implementation with - here's some important assumptions you can draw from them:
- There will always be an equal number of people wanting to take the elevator on both the ground and second floor. This means the elevator should always end the program on the ground floor.
- There will always be enough people to fill the elevator (assuming your implementation works correctly), even if you are waiting for some time.
- The elevator always starts on the ground floor.

TLDR - you shouldn't deadlock as a result of a bad testing scenario.

Here's some sample output of me running each scenario:
```
./elevator 1
```

```
./elevator 2
```

```
./elevator 3
```








