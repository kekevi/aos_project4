# CS 6210 Project 4: MapReduce Infrastructure

This project must be completed **individually**.

## Submission README Instructions
- This file is part of your submission and is worth **1 point**.
- Before you submit, feel free to **delete the current content** of this file and replace it with your own README.
- A good README should quickly explain what your project does and walk through the overall flow of your system.
- Please also highlight important design decisions, especially anything related to handling **slow workers** or **dead workers**.
- It is helpful to briefly mention how you tested your system and any external resources you used.
- The goal is for a reader to understand how your system works without needing to read all of your code.

## Project Interview

Project 4 includes a short oral interview after submission. The purpose of the interview is to verify that you understand the MapReduce infrastructure you submitted, including the overall dataflow, sharding and partitioning invariants, worker scheduling and concurrency, and failure handling. The interview is **not a second autograder** and is not intended to test memorization. You should be prepared to open your submitted code and explain how data and tasks move through your implementation and why the system remains correct when multiple, slow, or failed workers are involved.

- The interview itself will take about **15 minutes** and will be scheduled in a **20-minute appointment slot**.
- You are responsible for signing up for an interview slot by the announced deadline. If none of the available slots work for you, contact the head TAs as early as possible.
- Missing the interview without a valid documented reason will result in a **zero for the project**.
- Arriving more than **5 minutes late** may result in a **25% deduction from the project grade**.
- AI tools may be used according to the course AI policy, including any required disclosure/log submission. Regardless of tool use, you are responsible for understanding all code you submit.

### How the Interview Affects Your Project Grade

The autograder and existing project-grading components determine your **base project score**. The oral interview determines a multiplier between **0 and 1**, which is applied to the entire base project score:

```text
Final Project Score = Base Project Score × Oral Interview Multiplier
```

A student who demonstrates strong understanding of the submitted implementation should receive a multiplier close to 1. Correct output by itself does not guarantee a high interview multiplier if the student cannot explain the submitted design, correctness invariants, scheduling behavior, or failure handling.

### Interview Rubric

The interview will cover the following four areas. The weights below are the relative weights **within the oral interview multiplier**.

| Category | Weight | What you should be prepared to explain |
|---|---:|---|
| **A. Dataflow and Code Ownership** | 30% | The end-to-end MapReduce flow in your implementation, including input shards, worker map execution, intermediate data, reducer partitioning/grouping, reduce execution, and final output. You should be able to connect the explanation to your submitted code and distinguish framework logic from the user-provided MapReduce application logic. |
| **B. Sharding and Partitioning Invariants** | 30% | How input shards are constructed without skipping, duplicating, or splitting records incorrectly; how intermediate key/value pairs are assigned to reducers; why each key is reduced by exactly one reducer; and what output format is required. |
| **C. Scheduling and Concurrency** | 20% | How the master tracks workers and tasks, assigns work in parallel, protects shared scheduling state, handles slow workers without unnecessarily serializing the job, and ensures the reduce phase starts only after map tasks complete. |
| **D. Failure Handling and Cleanup** | 20% | How failed worker/RPC cases are detected and recovered from, what happens to in-progress work, how retries avoid corrupting or double-counting partial results, and how intermediate files are cleaned up. |

In general, **strong understanding** means that you can explain the relevant logic independently and connect your explanation directly to your submitted code. **Partial understanding** means that you understand the main idea but need prompting or are unclear on important implementation details. **Weak understanding** means that you cannot explain or locate important parts of your submitted implementation, or your explanation conflicts with the code you submitted.

### Example Question Styles

The questions below are **illustrative examples only**. They are intended to show the level and style of the interview; the actual questions and follow-up questions may differ and may be adapted to your implementation.

- "Walk us through one input record from the original file until its contribution appears in a final output file."
- "How does your implementation make sure input records and intermediate keys are partitioned correctly across map and reduce tasks?"
- "How does the master keep multiple workers busy while preventing the same task from being incorrectly assigned or completed twice?"
- "Suppose a worker fails while processing a task. What happens next, and how does your implementation preserve correctness?"

You do not need to memorize a script for the interview. The best preparation is to review your own submitted code and README and make sure you understand the complete dataflow, the invariants that make the output correct, the scheduling decisions made by the master, and your failure-recovery and cleanup behavior.

## Project Instructions
- [Project Description](description.md)  
- [Code Walkthrough](structure.md)

## Environment Setup
- Please use the **existing environment from Project 3** to set up this project.  
- Ensure all dependencies and environment settings are consistent with your previous setup.

## Notes
The data used in this assignment is sourced from publicly available materials on the internet, including popular literature. Please be aware that some content may contain inappropriate language or material. The **teaching team is not responsible** for and cannot control the presence of such content.

## Important Instructions
- Ensure that **all intermediate files** generated by map tasks are **deleted** once each MapReduce task is completed.  
- Failure to remove these temporary files **may result in test failures** on Gradescope.
