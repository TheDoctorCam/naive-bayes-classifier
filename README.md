# naive-bayes-classifier

 ## About

The Bayes Classifier (BC) is a probabilistic framework so solving
classification problems. A Naive Bayes Classifier (NBC) is an approximation of a BC, where we assume conditional independence P(X|Y, Z) = P(X|Z).

## Bayes Classification Example

A Doctor knows that meningitis causes a stiff neck 50% of the time. They also know that the probability of any patient having meningitis is 1/50,000 and the probability of a patient having a stiff neck is 1/20. If the patient has a stiff neck, what is the probability they also have meningitis?

```
            p(X|Y)p(Y)
1. p(Y|X) = ----------
            p(X)

            0.5 * (1/50,000)
2. p(Y|X) = ---------------- = 0.0002
            (1/20)
```

## Naive Bayes Classification 

A NBC considers each attribute and class label as random variables. Given a record with attributes (A :sub:`1`, A :sub:`2`,..., A  :sub:`n`), the goal is to find the value of C that maximizes P(C| A :sub:`1`, A :sub:`2`,..., A  :sub:`n`).