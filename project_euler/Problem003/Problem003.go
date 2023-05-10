package project_euler

import "fmt"

func Problem003() {
    target := int64(600851475143)
    for 0 == (target & 1) {
        target >>= 1
    }
    if 1 == target {
        target = 2
    }

    factor := int64(3)
    for factor < target {
        for 0 == target % factor && target != factor {
            target /= factor
        }
        factor += 2
    }
    fmt.Println(target)
}
